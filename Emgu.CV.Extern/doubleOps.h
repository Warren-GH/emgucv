#pragma once

#ifndef WEIGHTED_SUM_H
#define WEIGHTED_SUM_H

#include "sse.h"
namespace doubleOps
{
   inline void weightedSum(const double* d1, const double* d2, int elementCount, double w1, double w2, double* r)
   {
      double* end = r + elementCount;
#if EMGU_SSE2
      __m128d f = _mm_set_pd(w1, w2);
      while(r < end)
         *r++ = _dot_product(_mm_set_pd(*d1++, *d2++), f);
#else
      while( r < end) 
         *r++ = *d1++ * w1 + *d2++ * w2;
#endif
   }

   inline void mulS(const double* d, double scale, int length, double* result)
   {
      const double* current = d;
      const double* end = d+length;
#if EMGU_SSE2
      __m128d _scale = _mm_set1_pd(scale);
      for(const double* stop = d + (length & -2); current < stop; current+=2, result+=2)
         _mm_storeu_pd(result,_mm_mul_pd(_mm_loadu_pd(current), _scale));
#endif
      while (current < end)
      {
         *result++ = (*current++) * scale;
      }
   }
}
#endif