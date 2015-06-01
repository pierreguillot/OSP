/*
 // Copiesright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#ifndef __DEF_OSP__
#define __DEF_OSP__

#if (__cplusplus <= 199711L)
#define noexcept
#define nullptr NULL
#endif

namespace osp
{
    template <typename T> class Osp
    {
    public:
        
        //! Clears a vector.
        /** Clears a vector.
         @param size The size of the vector.
         @param in   The input vector.
         */
        static inline void clear(size_t const size, T* in) noexcept
        {
            memset(in, 0, size * sizeof(T));
        }
        
        //! Fills a vector a vector with a value.
        /** Fills a vector a vector with a value
         @param size  The size of the vector.
         @param value The value.
         @param in    The input vector.
         */
        static inline void fill(size_t const size, T const& value, T* in) noexcept
        {
            for(size_t i = size>>3; i; --i, in += 8)
            {
                in[0] = value; in[1] = value; in[2] = value; in[3] = value;
                in[4] = value; in[5] = value; in[6] = value; in[7] = value;
            }
            for(size_t i = size&7; i; --i, in++)
            {
                in[0] = value;
            }
        }
        
        //! Computes the dot product of two vectors.
        /** Computes the dot product of two vectors.
         @param   size   The size of the vectors.
         @param   in1    The first vector.
         @param   in2    The second vector.
         @return The dot product of the two vectors.
         */
        static inline T dot(const size_t size, const T* in1, const T* in2) noexcept
        {
            T result = 0;
            for(size_t i = size>>3; i; --i, in1 += 8, in2 += 8)
            {
                result += in1[0] * in2[0]; result += in1[1] * in2[1]; result += in1[2] * in2[2]; result += in1[3] * in2[3];
                result += in1[4] * in2[4]; result += in1[5] * in2[5]; result += in1[6] * in2[6]; result += in1[7] * in2[7];
            }
            for(size_t i = size&7; i; --i, in1++, in2++)
            {
                result += in1[0] * in2[0];
            }
            return result;
        }
    };
}

#endif
