
#include <stddef.h>

#include "poly_arith.h"

#include "NTT.h"

/* ----- rounded polynomials mod q */

void Round(Fq *out,const Fq *a)
{
  int i;
  int *o1 = (int *)(void *)out;
  int *a1 = (int *)(void *)a;

  for (i = (p-1)/2; i>0; i--) {
    *(o1++) = F3_round_x2(*(a1++));
  }
  out = (Fq *)(void *) o1;
  a = (Fq *)(void *) a1;
  *out = F3_round_x2(*a);
}

/* h = f*g in the ring Rq */
void Rq_mult_small(Fq *h, Fq *f, small *g){

  int32_t poly1_NTT[ARRAY_N];
  int32_t poly2_NTT[ARRAY_N];

  for(size_t i = NTRU_N; i < POLY_N; i++){
    f[i] = 0;
    g[i] = 0;
  }

  NTT_forward(poly1_NTT, f);
  NTT_forward_small(poly2_NTT, g);
  NTT_mul(poly1_NTT, poly1_NTT, poly2_NTT);
  NTT_inv(h, poly2_NTT, poly1_NTT);
}

#ifdef LPR

/* ----- Top and Right */

#define tau 16
/*************************************************
* Name:        Top
*
* Description: Round ((tau_1 * (C+tau_0)) div 2^15) to the closer integer and return.
*
* Arguments:
* Fq C     : input coefficient
*
**************************************************/
int8 Top(Fq C)
{
  return (tau1*(int32)(C+tau0)+16384)>>15;
}

/*************************************************
* Name:        Right
*
* Description: Compute (tau_3*T-tau_3) mod q.
*
* Arguments:
* int8 T   : input coefficient
**************************************************/
Fq Right(int8 T)
{
  return Fq_freeze(tau3*(int32)T-tau2);
}

void Rq_mult_twice(Fq *bG, Fq *bA, Fq *G, Fq *A, small *b){

  int32_t poly1_NTT[ARRAY_N];
  int32_t poly2_NTT[ARRAY_N];
  int32_t buff[ARRAY_N];

  for(size_t i = NTRU_N; i < POLY_N; i++){
    G[i] = 0;
    A[i] = 0;
    b[i] = 0;
  }

  NTT_forward_small(poly2_NTT, b);
  NTT_forward(poly1_NTT, G);
  NTT_mul(poly1_NTT, poly1_NTT, poly2_NTT);
  NTT_inv(bG, buff, poly1_NTT);
  NTT_forward(poly1_NTT, A);
  NTT_mul(poly1_NTT, poly1_NTT, poly2_NTT);
  NTT_inv(bA, buff, poly1_NTT);

}

#else

/*************************************************
* Name:        R3_fromRq
*
* Description: Return a polynomial that i-th coefficient
*              computed as (r[i] mod q) mod 3.
*
* Arguments:
* small *out  : pointer to the output polynomial in R_3
* const Fq *r : pointer to the input polynomial in R_q
**************************************************/
void R3_fromRq(small *out,const Fq *r)
{
  int i;
  for (i = 0;i < p;++i) out[i] = F3_freeze_short(r[i]);
}

extern void copy_p_F3_mod3(const small *, small *, const small *, small *);
extern void gf_polymul_896x896_mod3(small *, small *, small *);
extern void reduce_2p_minus1_mod3_F3(small *, small *);
/* h = f*g in the ring R3 */
void R3_mult(small *h,const small *f,const small *g)
{
  small fg[1892];
  small f_mod3[896];
  small g_mod3[896];
  int i;
  for(i=857;i<896;++i)f_mod3[i]=g_mod3[i]=0;
  copy_p_F3_mod3(f, f_mod3, g, g_mod3);
  gf_polymul_896x896_mod3(fg, f_mod3, g_mod3);
  reduce_2p_minus1_mod3_F3(h, fg);
}

/* ----- polynomials mod q */

/* h = 3f in Rq */
void Rq_mult3(Fq *h,const Fq *f)
{
  int i;

  for (i = 0;i < p;++i) h[i] = Fq_freeze(3*f[i]);
}

#endif







