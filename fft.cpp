//---------------------------------------------------------------------------

#pragma hdrstop

#include "fft.h"
#include <malloc.h>
#include <math.h>
#include <stdio.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

void cdft( struct rcomplex d[], struct rcomplex r[], long nv, int t )
{
/* *****************************************************************

   This routine computes either a discrete Fourier transform or inverse
   discrete Fourier transform.

   Parameters include:

      d[]:  Complex input data array.
      r[]:  Complex result array.
      nv:   Number of input data values.
      t:    Flag for transform type:  DFT if t > 0, IDFT if t <= 0.

   The DFT is given by:

   X(k) = SIGMA n -> 0 TO N-1: ( x(n) * EXP( -j * 2PI * k * n / N ))

   -- and the IDFT is given by:

           1
   x(n) = --- * SIGMA k -> 0 TO N-1: ( X(k) * EXP( j * 2PI * k * n / N ))
           N

   The complex exponentials are computed by:

   EXP( j * p )  = COS( p ) + j * sin( p )
   EXP( -j * p ) = COS( p ) - j * sin( p )

   -- and the complex multiplication is performed with:

   ( R1 + j * I1 ) * ( R2 + j * I2 )

                   = ( R1 * R2 - I1 * I2 ) + j * ( R1 * I2 + I1 * R2 )

   Both the input data array d[] and the result data array r[] are complex
   arrays.

   Local variables include:

      f:     Multiplying factor.
      tmp:   Temporary complex results.
      tsum:  Temporary sum.
      nr:    Results count.
      nd:    Data count.
      s:     Sign of imaginary component (-1 for DFT, 1 for IDFT).

   ******************************************************************* */

  double f;
  struct rcomplex tmp, tsum;
  long nr, nd;
  int s;

  s = ( t > 0 ) ? -1 : 1;                 /* Set DFT (-1) or IDFT (1). */

  for ( nr = 0; nr <= ( nv - 1 ); ++nr )
  {
    f = 8 * atan(1) * nr / nv;
    tsum.re = 0;
    tsum.im = 0;
    for ( nd = 0; nd <= (nv - 1); ++nd )  /* Crunch one result.  */
    {
      tmp.re = cos( f * nd );
      tmp.im = s * sin( f * nd );
      tsum.re += d[nd].re * tmp.re - d[nd].im * tmp.im;
      tsum.im += d[nd].re * tmp.im + d[nd].im * tmp.re;
    }
    r[nr] = tsum;
  }

  if ( s == 1 )                           /* If IDFT, scale results. */
  {
    for ( nr = 0; nr <= (nv - 1); ++nr )
    {
      r[nr].re = r[nr].re / nv;
      r[nr].im = r[nr].im / nv;
    }
  }
}


void cfft( struct rcomplex d[], long nv, int t )
{
/* *****************************************************************

   This routine computes either a Fast Fourier transform or inverse Fast
   Fourier transform.  Parameters include:

      d[]:  Complex data array.
      nv:   Number of input data values.
      t:    Flag for transform type:  FFT if t > 0, IFFT if t <= 0.

   This routine is based on the equations for the discrete Fourier
   transform:

   X(k) = SIGMA n -> 0 TO N-1: ( x(n) * EXP( -j * 2PI * k * n / N ))

   -- and the inverse discrete Fourier transform:

           1
   x(n) = --- * SIGMA k -> 0 TO N-1: ( X(k) * EXP( j * 2PI * k * n / N ))
           N
  
   The complex exponentials are computed by:
  
   EXP( j * p )  = COS( p ) + j * sin( p )
   EXP( -j * p ) = COS( p ) - j * sin( p )
  
   -- and the complex multiplication is performed with:
  
   ( R1 + j * I1 ) * ( R2 + j * I2 )
  
                   = ( R1 * R2 - I1 * I2 ) + j * ( R1 * I2 + I1 * R2 )
  
   The complex data array d[] provides the input data and returns the
   output data -- the computation is done "in place".
  
   Local variables include:
  
      tmp:       Temporary complex results.
      w:         Complex twiddle factor.
      arg:       Argument for tiddle factor.
      x1,x2,x3:  Various indexing factors.
      f1,f2:     Various factors.
      n:         Index.
      nrev:      Bit-reversed index.
      pow2:      Current power of 2.
      B:         Butterfly count.
      hibit:     Maximum bit.
      nbit:      Bit counter.
      s:         Sign of imaginary component (-1 for FFT, 1 for IFFT).

   ******************************************************************* */

  struct rcomplex tmp, w;
  double arg;
  long x1, x2, x3, f1, f2, n, nrev, pow2, b;
  int hibit, nbit, s;

  s = ( t > 0 ) ? -1 : 1;                    /* Set FFT (-1) or IFFT (1). */

  hibit = (int)(0.5 + log(nv) / log(2)) - 1; /* Determine number of bits. */

  for ( n = 0; n <= (nv - 1); ++n )          /* Perform bit reversal. */
  {
    f1 = n;
    nrev = 0;
    for ( nbit = 0; nbit <= hibit; ++nbit )
    {
      f2 = (int)(f1 / 2);
      nrev = nrev + ( pow( 2, hibit - nbit ) * (f1 - (2 * f2)));
      f1 = f2;
    }
    if ( nrev > n )                          /* Reversed, now swap. */
    {
      tmp = d[nrev];
      d[nrev] = d[n];
      d[n] = tmp;
    }
  }

  for ( nbit = 0; nbit <= hibit; ++nbit )       /* Perform FFT. */
  {
    pow2 = pow( 2, nbit );
    x1 = ((nv / pow2) / 2) - 1;
    for ( n = 1; n <= pow2; ++n )
    {
      arg = 4 * atan(1) * (n - 1) / pow2;   /* Compute twiddle factor. */
      w.re = cos(arg);
      w.im = s * sin(arg);
      for ( b = 0; b <= x1; ++b )           /* Compute butterflies. */
      {
        x2 = (pow2 * b * 2) + n - 1;
        x3 = x2 + pow2;
        tmp.re = d[x3].re * w.re  -  d[x3].im * w.im;
        tmp.im = d[x3].re * w.im  +  d[x3].im * w.re;
        d[x3].re = d[x2].re  -  tmp.re;
        d[x3].im = d[x2].im  -  tmp.im;
        d[x2].re = d[x2].re  +  tmp.re;
        d[x2].im = d[x2].im  +  tmp.im;
      }
    }
  }

  if ( s == 1 )                             /* If IFFT, then scale. */
  {
    for ( n = 0; n <= (nv - 1); ++n )
    {
      d[n].re = d[n].re / nv;
      d[n].im = d[n].im / nv;
    }
  }
}


void conv( double d[], double f[], double r[], long c[] )
{
/* ***************************************************************** 

   This little subprogram computes either a convolution or correlation,
   depending on the setting of the C(2) variable.

   Parameters include:

     d[]:     Double data array of nv elements.
     f[]:     Function values of nc elements.
     r[]:     Double result array of (nv + nc -1) elements.
     c[]:     Control data:
  
              c[0]:  Number of data points.
              c[1]:  Number of points in convolution function.
              c[2]:  Convolution if c[2] <=0, correlation if c[2] > 0.
  
   Local variables include:

     nv:      Number of data values.
     nc:      Number of values in function.
     n1:      Outer loop index counter.
     n2:      Inner loop index counter.
     n3:      Offset index counter. 

   ******************************************************************* */

  long nv, nc, nr;
  long n1, n2;

  nv = c[0];
  nc = c[1];

  for ( n1 = 0; n1 <= (nv + nc - 2); ++n1 )  /* Zero result array. */
  {
    r[n1] = 0;
  }

  if ( c[2] <= 0 )                      /* Convolution. */
  {
    for ( n1 = 0; n1 <= (nv - 1); ++n1 )
    {
      for ( n2 = 0; n2 <= (nc - 1); ++n2 )
      {
        r[n1 + n2] = r[n1 + n2]  +  d[n1] * f[n2];
      }
    }
  }
  else                                  /* Correlation. */
  {
    for ( n1 = 0; n1 <= (nv - 1); ++n1 )
    {
      for ( n2 = 0; n2 <= (nc - 1); ++n2 )
      {
        r[n1 + n2] = r[n1 + n2]  +  d[n1] * f[(nc - 1) - n2];
      }
    }
  }
}


void dfs( double d[], struct rcomplex r[], long nv )
{
/* ***************************************************************** 

   This routine computes the harmonic coefficients of a discrete Fourier
   series of a real data set.

   Parameters:

      d[]:  Double input data array.
      r[]:  Complex result (coefficient) array.
      nv:   Number of input data values.

   The computation is based on the formula:

   ak = ( 1/N ) * SIGMA k = 0 TO N-1:  x(n) * EXP( -j * 2PI * k * n / N )

   The complex exponential is computed using the equation:

   EXP( j * p ) = COS( p ) + j * sin( p )

   It computes the results in a complex array r[].

   Local variables include:

      f:     Multiplying factor.
      tsum:  Complex temporary sum.
      k:     Harmonic coefficient (result) count.
      n:     Data sample count.

   ******************************************************************* */

  double f;
  struct rcomplex tsum;
  long k, n;

  for ( k = 0; k <= (nv -1); ++k )      /* Step through harmonics. */
  {
    f = 8 * atan(1) * k / nv;
    tsum.re = 0;
    tsum.im = 0;
    for (n = 0; n <= (nv - 1); ++n )    /* Compute coefficients. */
    {
      tsum.re  +=  d[n] * cos(f * n);
      tsum.im  -=  d[n] * sin(f * n);
    }
    r[k].re = tsum.re / nv;
    r[k].im = tsum.im / nv;
  }
}

void dwinfunctest( void )
{
/* *******************************************************************

   Subprogram to test data windowing functions.

   ******************************************************************* */

  double d[16], r[16], m[8];
  struct rcomplex x[16], ak[16];
  double tmp, dstep, f;
  long n, nv = 16;

  for ( n = 0; n <= (nv - 1); ++n )
  {
    d[n] = 1;
  }

/* Test Bartlett (triangular) window. */

  f = 8 * atan(1);
  for ( n = 0; n <= (nv - 1); ++n )
  {
    r[n] = (1 - fabs(2 * n - nv + 1) / nv ) * d[n];
  }
  prreal( r, nv, "Bartlett Window" );

/* Test Blackman window. */

  f = (8 * atan(1)) / (nv - 1);
  for ( n = 0; n <= (nv - 1); ++n )
  {
    r[n] = (.42 - .5 * cos(f * n) + .08 * cos(2 * f * n)) * d[n];
  }
  prreal( r, nv, "Blackman Window" );

/* Test Hamming window. */

  f = 8 * atan(1);
  for ( n = 0; n <= (nv - 1); ++n )
  {
    r[n] = (.54 - .46 * cos(f * n / (nv - 1))) * d[n];
  }
  prreal( r, nv, "Hamming Window" );

/* Test Hanning window. */

  f = 8 * atan(1);
  for ( n = 0; n <= (nv - 1); ++n )
  {
     r[n] = .5 * (1 - cos(f * n / (nv - 1))) * d[n];
  }
  prreal( r, nv, "Hanning Window" );

/* Now demonstrate windowing ... first, get a full sine wave. */

  dstep = 8 * atan(1) / nv;
  for ( n = 0; n <= (nv - 1); ++n )
  {
    x[n].re = sin(n * dstep);
    x[n].im = 0;
  }
  prcomplex( x, nv, "Input Data (Sin)" );

/* Now get its DFT. */

  cdft( x, ak, nv, 1);
  magspec( ak, m, nv, nv );
  prreal( m, nv / 2, "Output Data (No Window)" );

/* Truncate it. */

  dstep = 8 * atan(1) / (nv + 3);
  for ( n = 0; n <= (nv - 1); ++n )
  {
    x[n].re = sin(n * dstep);
    x[n].im = 0;
  }
  prcomplex( x, nv, "Input Data (Truncated Sin)" );

/* Compute its DFT. */

  cdft( x, ak, nv, 1 );
  magspec( ak, m, nv, nv );
  prreal( m, nv / 2, "Output Data (No Window)" );

/* Now put the data through a Hamming window. */

  f = 8 * atan(1);
  for( n = 0; n <= (nv - 1); ++n )
  {
    x[n].re = (.54 - .46 * cos(f * n / (nv - 1))) * x[n].re;
  }
  prcomplex( x, nv, "Windowed Input Data (Truncated Sin)" );

/* Compute its DFT. */

  cdft( x, ak, nv, 1 );
  magspec( ak, m, nv, nv );
  prreal( m, nv / 2, "Output Data (Hamming Window)" );
}

void fir( double d[], double f[], double r[], long n[] )
{
/* *****************************************************************

   This subprogram computes an FIR filter response as per the formula:

     y(n) = a0 * x(n) + a1 * x(n - 1) + ... + ak * x(n - k)

   The input parameters are as follows:

      d[]:   Input data array.
      f[]:   Filter coefficients.
      r[]:   Result data.

      n[0]:  Length of input & result data arrays.
      n[1]:  Number of filter coefficients.

   Local variables include:

      nv:    Number of values.
      nf:    Number of filter coefficients.
      cv:    Value counter.
      cf:    Coefficient counter.

   ******************************************************************* */

  long cv, cf, nv, nf;
  nv = n[0];
  nf = n[1];

  for ( cv = 0; cv <= (nv - 1); ++cv )
  {
    r[cv] = 0;
    cf = 0;
    while (((cv - cf) >= 0) && (cf < nf))
    {
      r[cv] = r[cv] + f[cf] * d[cv - cf];
      ++cf;
    }
  }
}

void iir( double d[], double f[], double r[], long n[] )
{
/* *******************************************************************

   This subprogram computes an IIR filter response as per the formula:

      y(n) = x(n) + a1 * y(n-1) + ... + ak * y(n-k)

   The input parameters are as follows:

      d[]:   Input data array.
      f[]:   Filter coefficients.
      r[]:   Result data.

      n[0]:  Length of input & output data arrays (same as nv).
      n[1]:  Number of filter coefficients (same as nf).

   Local variables include:

      nv:    Number of values.
      nf:    Number of filter coefficients.
      cv:    Value counter.
      cf:    Coefficient counter.

   ******************************************************************* */

  long cv, cf, nv, nf;
  nv = n[0];
  nf = n[1];

  for ( cv = 0; cv <= (nv - 1); ++cv )
  {
    r[cv] = d[cv];
    cf = 0;
    while (((cv - (cf + 1)) >= 0) && (cf < nf))
    {
       r[cv] = r[cv] + f[cf] * r[cv - (cf + 1)];
       ++cf;
    }
  }
}

void magspec( struct rcomplex d[], double m[], long nv, long asize )
{
/* *******************************************************************

   This little routine takes a complex input spectrum and computes the
   normalized magnitude spectrum, consisting of positive values running
   from a DC term to the highest positive harmonic.

   Parameters include:

      d[]:    Complex spectral data array.
      m[]:    1-dimensional magnitude-spectrum array.
      nv:     Number of original time samples that produced the spectrum.
      asize:  Size of complex input array.

   Local variables include:

      n:      Counter from bottom.
      nh:     Counter from top.

   Note that the number of return magnitude values is only half that of
   the number of original sample values, because the magnitude spectrum
   merges the positive and negative frequency values.

   You can give the routine either the full complex spectrum with DC term,
   positive frequency values, and negative frequency values -- or you can
   just give it the DC term and positive frequency values (as would be
   obtained by a real-only FFT) ... it will work in either case.

   ******************************************************************* */

  long n, nh;

  for ( n = 1; n <= (asize - 1); ++n )  /* Zero result array. */
  {
     m[n] = 0;
  }

  m[0] = d[0].re / nv;                  /* DC term. */
  if ( nv == asize )                    /* Compute with full data set. */
  {
    nh = asize - 1;                     /* Get upper bound of data. */
    n = 1;
    do
    {
      m[n] = pow( d[n].re + d[nh].re, 2 ) + pow( d[n].im - d[nh].im, 2 );
      m[n] = sqrt( m[n] ) / nv;
      ++n;
      --nh;
    }
    while ( n < nh );
  }
  else                                  /* Compute with half data set. */
  {
    for ( n = 1; n <= (asize - 1); ++n )
    {
      m[n] = 2 * sqrt( d[n].re * d[n].re + d[n].im * d[n].im ) / nv;
    }
  }
}


void mvavg( double d[], double r[], long c[] )
{
/* *********************************************************************

   This little subprogram computes a moving average.  Parameters include:

      d[]:     Double data array.
      r[]:     Double result array.
      c[]:     Control data:

               c[0]:  Number of data points.
               c[1]:  Averaging interval.
               c[2]:  Flag to determine handling of data at endpoints.

   The c[2] flag is set to 0 if you want to assume data beyond the endpoints
   is zero, and set to 1 if you want to assume that the data beyond the
   endpoints has the same value as that of the endpoints; that is, if
   if d[0] = 101, then the data preceding it are assumed to all have
   the value of 101 as well.

   Local variables include:

      nv:      Number of data values.
      na:      Averaging interval.
      f:       Endpoint-handling flag.
      n1:      Outer loop index counter.
      n2:      Inner loop index counter.
      lo:      Low value offset.
      hi:      High value offset.

   This routine is designed for simplicity; much can be done to make it
   more efficient at the cost of a little complexity, but that is an
   exercise for the reader.

   ******************************************************************* */

  long nv, na, f;
  long n1, n2, lo, hi;

  nv = c[0];
  na = c[1];
  f  = c[2];

  lo = -(int)(na / 2);                   /* Get low index offset. */
  hi = na - (int)(na / 2) - 1;           /* Get high index offset. */

  for ( n1 = 0; n1 <= (nv - 1); ++n1 )   /* Step through data. */
  {
    r[n1] = 0;
    for ( n2 = (n1 + lo); n2 <= (n1 + hi); ++n2 )
    {
      if ( n2 < 0 )                      /* Index below data values. */
      {
        if ( f == 1 )
	{
          r[n1] += d[0];                 /* Use low data value instead. */
        }
      }
      else
      {
        if ( n2 >= nv )                  /* Index above data values. */
	{
          if ( f == 1 )
	  {
            r[n1] += d[nv - 1];          /* Use high data value instead. */
          }
        }
        else                             /* Otherwise, average data. */
	{
          r[n1] += d[n2];
        }
      }
    }
    r[n1] = r[n1] / na;                  /* Average data. */
  }
}

void phasespec( struct rcomplex d[], double p[], long nv, long asize )
{
/* *******************************************************************

   This little routine takes a complex input spectrum and computes the
   phase spectrum for positive values running the DC term to the highest
   positive harmonic.

   Parameters include:

      d[]:    Complex spectral data array.
      d[]:    Phase-spectrum array.
      dv:     Number of original time samples that produced the spectrum.
      dsize:  Size of input array.

   Note that the number of return phase items is only half that of
   the number of sample values, since we only consider the positive
   frequency values.

   You can give the routine either the full complex spectrum with DC term,
   positive frequency values, and negative frequency values -- or you can
   just give it the DC term and positive frequency values (as would be
   obtained by a real-only FFT) ... it will work in either case.

   Local variables include:

      n:      Counter from bottom.
      nh:     Counter from top.

   ******************************************************************* */

  long n, nh;

  for ( n = 1; n <= (asize - 1); ++n )  /* Zero result array. */
  {
     p[n] = 0;
  }

  p[0] = 0;                              /* DC term. */
  if ( nv == asize )                     /* Compute with full data set. */
  {
    nh = asize - 1;                      /* Get upper bound. */
    n = 1;
    do
    {
      p[n] = atan(( d[n].im - d[nh].im) / (d[n].re + d[nh].re));
      ++n;
      --nh;
    }
    while ( n < nh );
  }
  else                                   /* Compute with half data set. */
  {
    for ( n = 1; n <= (asize - 1); ++n )
    {
      p[n] = atan(d[n].im / d[n].re);
    }
  }
}

void prcomplex( struct rcomplex c[], long asize, char *s )
{
/* *******************************************************************

   This little routine simply prints a complex number array to standard
   output.

   ******************************************************************* */

  long n;
  char *l = "------------------------";

  puts( s );
  puts( l );
  for ( n = 0; n <= (asize - 1); ++n )
  {
      printf( "%2ld %10.4f %10.4f\n", n, c[n].re, c[n].im ); 
  }
  puts( l );
}

void prreal( double r[], long asize, char *s )
{
/* *******************************************************************

   This little routine simply prints a real number array to the standard
   output.

   ******************************************************************* */

  long n;
  char *l = "------------------------";

  puts( s );
  puts( l );
  for ( n = 0; n <= (asize - 1); ++n )
  {
    printf( "%2ld   %10.4f\n", n, r[n] );
  }
  puts( l );
}

void rfft( double d[], struct rcomplex r[], long nv )
{
/* *******************************************************************

   This routine massages an input sequence of real data values for
   computing an efficient FFT using the CFFT routine.

   Parameters include:

      d[]:  Double real input data array.
      r[]:  Complex result array.
      nv:   Number of input data values.

   In general terms, the conversion is done by converting the
   real-valued input array of length nv into a complex array of
   length nv/2 (where the even-valued input elements become the
   real components and the odd-valued input elements become the
   imaginary components).

   This array is then passed on to the CFFT subprogram for computing
   its FFT; on return, the FFT data is rearranged into its appropriate
   data values.

   The input data array d[] is just a 1-dimensional array that stores the
   real input data, while the result array r[] is a two-dimensional array,
   where the first row stores the real value and the second row stores
   the imaginary value.

   Note that the complex output array is half the length (nv/2) of the
   real input array.  This is because in a real DFT, the spectrum consists
   of a single "DC" value, a set of complex numbers designating positive
   frequencies, and a mirror set of complex-conjugate numbers designating
   negative frequencies.  This means that the routine only has to return
   the "DC" term and the positive-frequency terms, since the
   negative-frequency terms can be derived from the positive-frequency
   terms.

   Local variables include:

      tsum:    Temporary complex sum.
      tdif:    Temporary complex difference.
      cf:      Complex coefficient.
      s:       Intermediate complex array.
      f:       Trig factor.
      n:       Low index.
      nhi:     High index.

   ******************************************************************* */

  struct rcomplex tsum, tdif, cf;
  double f;
  long n, nhi;
  struct rcomplex *s;                             /* Pointer to array. */
  s = (struct rcomplex *)malloc( sizeof(double) * (short)(nv) );

/* Copy data to result array. */

  for ( n = 0; n <= (nv / 2 - 1); ++n )
  {
    s[n].re = d[2 * n];
    s[n].im = d[2 * n + 1];
  }

  cfft( s, nv / 2, 1 );             /* Compute the FFT. */

  r[0].re = s[0].re + s[0].im;        /* Compute DC term. */
  r[0].im = 0;

  f = 8 * atan(1) / nv;               /* Factor for trig computations. */
  nhi = nv / 2 - 1;
  for ( n = 1; n <= ( nv / 2 - 1 ); ++n )
  {
    cf.re = cos(f * n);
    cf.im = sin(f * n);
    tsum.re = ( s[n].re + s[nhi].re ) / 2;
    tsum.im = ( s[n].im + s[nhi].im ) / 2;
    tdif.re = ( s[n].re - s[nhi].re ) / 2;
    tdif.im = ( s[n].im - s[nhi].im ) / 2;
    r[n].re = tsum.re + cf.re * tsum.im - cf.im * tdif.re;
    r[n].im = tdif.im - cf.im * tsum.im - cf.re * tdif.re;
    --nhi;
  }
  free( s );                                     /* Release memory. */
}

void testcdft( void )
{
/* *******************************************************************

   Subprogram to test DFT and IDFT.

   ******************************************************************* */

  struct rcomplex x[16], ak[16];
  double tmp;
  long n, nv = 16;

  for ( n = 0; n <= (nv - 1); ++n )
  {
    tmp = .375 * n;
    x[n].re = exp(-tmp) * sin(tmp);
    x[n].im = 0;
  }

  prcomplex(  x, nv, "DFT Input Data" );
  cdft( x, ak, nv, 1 );                          /* Compute DFT. */
  prcomplex( ak, nv, "DFT Results" );
  cdft( ak, x, nv, 0 );                          /* Compute IDFT. */
  prcomplex(  x, nv, "Inverse DFT Results" );
}

void testcfft( void )
{
/* *******************************************************************

   Subprogram to test FFT and IFFT.

   ******************************************************************* */

  struct rcomplex d[16];
  double tmp;
  long n, nv = 16;

  for ( n = 0; n <= (nv - 1); ++n )
  {
    tmp = .375 * n;
    d[n].re = exp(-tmp) * sin(tmp);
    d[n].im = 0;
  }
  prcomplex( d, nv, "CFFT Input Data" );
  cfft( d, nv, 1 );                            /* Compute FFT. */
  prcomplex( d, nv, "CFFT Result Data" );
  cfft( d, nv, 0 );                            /* Compute IFFT. */
  prcomplex( d, nv, "CIFFT Result Data" );
}

void testconv( void )
{
/* *******************************************************************
 
   This routine runs a simple set of tests on the convolution routine.

   ******************************************************************* */

   long nv, c[3];
   double d[12], f[5], r[16];

   d[0] = 1;                               /* Data points */
   d[1] = 2;
   d[2] = 3;
   d[3] = -1;

   f[0] = 1;                               /* Convoluting function. */
   f[1] = -1;
   f[2] = 2;

   c[0] = 4;
   c[1] = 3;
   c[2] = 0;

   prreal( d, 4, "Data To Be Convoluted" );
   prreal( f, 3, "Convoluting Function" );
   conv( d, f, r, c );
   prreal( r, 6, "Convolution Result (1)" );

   c[2] = 1;
   conv( d, f, r, c );
   prreal( r, 6, "Correlation Result (1)" );

   f[0] = 2;                               /* Convoluting function. */
   f[1] = -1;
   f[2] = 1;
   c[2] = 0;

   conv( d, f, r, c );
   prreal( r, 6, "Convolution Result (1)" );

   c[2] = 1;
   conv( d, f, r, c );
   prreal( r, 6, "Correlation Result (2)" );

   d[0] = 100;
   d[1] = 92;
   d[2] = 110;
   d[3] = 125;
   d[4] = 103;
   d[5] = 115;
   d[6] = 96;
   d[7] = 105;
   d[8] = 130;
   d[9] = 97;
   d[10] = 113;
   d[11] = 135;
   c[0] = 12;

   f[0] = 1.0/3.0;
   f[1] = 1.0/3.0;
   f[2] = 1.0/3.0;
   c[1] = 3;

   prreal( d, 12, "Moving Average Data" );
   conv( d, f, r, c );
   prreal( r, 14, "3-Point Moving Average" );

   f[0] = 0.2;
   f[1] = 0.2;
   f[2] = 0.2;
   f[3] = 0.2;
   f[4] = 0.2;
   c[1] = 5;

   conv( d, f, r, c );
   prreal( r, 16, "5-Point Moving Average" );
}

void testdfs( void )
{
/* *******************************************************************

   Subprogram to test DFS.

   ******************************************************************* */

  double x[7] = { 2, 1, -2, 3, -1, -1, 1 };
  double m[7], p[7];
  struct rcomplex ak[7];
  int n;

  dfs( x, ak, 7 );
  prcomplex( ak, 7, "DFS Data" );
  magspec( ak, m, 7, 7 );
  prreal( m, 7, "Magspec data" );
  phasespec( ak, p, 7, 7 );
  prreal( p, 7, "Phasespec data" );
}

void testfir( void )
{
/* *******************************************************************

   This routine tests the fir() routine.

   ******************************************************************* */

   double r[13];
   double d[12] = { 100,92,110,125,103,115,96,105,130,97,113,135 };
   double f[3] = { 0.25, 0.5, 0.25 };
   long n[2] = { 12, 3 };

   fir( d, f, r, n );
   prreal( r, 10, "FIR data" );
}

void testiir( void )
{
/* *******************************************************************

   This routine tests the iir() routine.

   ******************************************************************* */

   double r[13];
   double d[12] = { 100,92,110,125,103,115,96,105,130,97,113,135 };
   double f[3] = { 0.25, 0.5, 0.25 };
   long n[2] = { 12, 3 };

   iir( d, f, r, n );
   prreal( r, 10, "IIR data" );
}

void testmvavg( void )
{
/* *******************************************************************

   This routine runs a simple set of tests on the moving average routine.

   ******************************************************************* */

   double r[12];
   double d[12] = { 100,92,110,125,103,115,96,105,130,97,113,135 };
   long nv = 12, c[3] = { 12, 3, 0 };

   prreal( d, nv, "Moving Average Data" );
   mvavg( d, r, c );
   prreal( r, nv, "3-Point Moving Average" );
   c[1] = 5;
   mvavg( d, r, c );
   prreal( r, nv, "5-Point Moving Average" );
}

void testrfft( void )
{
/* *******************************************************************

   Subprogram to test real FFT.

   ******************************************************************* */

  struct rcomplex r[9];
  double d[16], m[9], p[9];
  double tmp;
  long n, nv = 16;

  for ( n = 0; n <= (nv - 1); ++n )
  {
    tmp = .375 * n;
    d[n] = exp(-tmp) * sin(tmp);
  }

  prreal( d, nv, "RFFT Input Data" );
  rfft( d, r, nv );
  prcomplex( r, nv / 2, "RFFT Result Data" );
  magspec( r, m, nv, nv / 2 );
  prreal( m, nv / 2, "Magspec data" );
  phasespec( r, p, nv, nv / 2 );
  prreal( p, nv / 2, "Phasespec data" );
}

void hamming(struct rcomplex r[],int nv)
{
  double f = 8 * atan(1);
  int n;
  for ( n = 0; n <= (nv - 1); ++n )
  {
    r[n].re = (.54 - .46 * cos(f * n / (nv - 1))) * r[n].re;
    r[n].im = (.54 - .46 * cos(f * n / (nv - 1))) * r[n].im;
  }
}

void FFT::Calc()
{
    int i;

    for(i=0;i<size;i++)
    {
       out[i].re = 0;
       out[i].im = 0;
    }

    hamming(in,size);
    cfft(in,size,1);
    for(i=0;i<size;i++)
    {
       out[i].re = in[i].re;
       out[i].im = in[i].im;
    }

    for(i=0;i<size/2;i++)
    {
       ampl[i] = sqrt(out[i].re*out[i].re+out[i].im*out[i].im);
    }
}
