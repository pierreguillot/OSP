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
        
        //! Fills a vector with a value.
        /** Fills a vector with a value
         @param size  The size of the vector.
         @param value The value.
         @param in    The input vector.
         */
        static inline void fill(size_t const size, T const& value, T* in) noexcept
        {
            const T vec[8] = {value, value, value, value, value, value, value, value};
            for(size_t i = size>>3; i; --i, in += 8)
            {
                memcpy(in, vec, 8 * sizeof(T));
            }
            if(size&7)
            {
                memcpy(in, vec, (size&7) * sizeof(T));
            }
        }
        
        //! Swaps two vectors.
        /** Swaps two vectors.
         @param size The size of the vectors.
         @param in1  The first vector.
         @param in2  The second vector.
         */
        static inline void swap(const size_t size, T* in1, T* in2) noexcept
        {
            T vec[8];
            for(size_t i = size>>3; i; --i, in1 += 8, in2 += 8)
            {
                memcpy(vec, in1, 8 * sizeof(T));
                memcpy(in1, in2, 8 * sizeof(T));
                memcpy(in2, vec, 8 * sizeof(T));
            }
            if(size&7)
            {
                memcpy(vec, in1, (size&7) * sizeof(T));
                memcpy(in1, in2, (size&7) * sizeof(T));
                memcpy(in2, vec, (size&7) * sizeof(T));
            }
        }
        
        //! Copies a vector into another.
        /** Copies a vector into another.
         @param size The size of the vectors.
         @param in   The input vector.
         @param out  The output vector.
         */
        static inline void copy(const size_t size, const T* in, T* out) noexcept
        {
            for(size_t i = size>>3; i; --i, in += 8, out += 8)
            {
                memcpy(out, in, 8 * sizeof(T));
            }
            if(size&7)
            {
                memcpy(out, in, (size&7) * sizeof(T));
            }
        }
        
        //! Adds a vector to another.
        /** Adds a vector to another.
         @param size The size of the vectors.
         @param in   The input vector.
         @param out  The output vector.
         */
        static inline void add(const size_t size, const T* in, T* out) noexcept
        {
            for(size_t i = size>>3; i; --i, in += 8, out += 8)
            {
                out[0] += in[0]; out[1] += in[1]; out[2] += in[2]; out[3] += in[3];
                out[4] += in[4]; out[5] += in[5]; out[6] += in[6]; out[7] += in[7];
            }
            for(size_t i = size&7; i; --i, in++, out++)
            {
                out[0] += in[0];
            }
        }
        
        //! Adds a two vectors and leaves the result in another.
        /** Adds a two vectors and leaves the result in another.
         @param size The size of the vectors.
         @param in1  The first input vector.
         @param in2  The second input vector.
         @param out  The output vector.
         */
        static inline void add(const size_t size, const T* in1, const T* in2, T* out) noexcept
        {
            for(size_t i = size>>3; i; --i, in1 += 8, in2 += 8, out += 8)
            {
                const T f0 = in1[0], f1 = in1[1], f2 = in1[2], f3 = in1[3];
                const T f4 = in1[4], f5 = in1[5], f6 = in1[6], f7 = in1[7];
                out[0] = f0 + in2[0]; out[1] = f1 + in2[1]; out[2] = f2 + in2[2]; out[3] = f3 + in2[3];
                out[4] = f4 + in2[4]; out[5] = f5 + in2[5]; out[6] = f6 + in2[6]; out[7] = f7 + in2[7];
            }
            for(size_t i = size&7; i; --i, in1++, in2++, out++)
            {
                out[0] += in1[0] + in2[0];
            }
        }
        
        //! Adds a scalar to a vector.
        /** Adds a scalar to a vector.
         @param size  The size of the vectors.
         @param value The value.
         @param in    The vector.
         */
        static inline void add(const size_t size, T const& value, T* in) noexcept
        {
            for(size_t i = size>>3; i; --i, in += 8)
            {
                in[0] += value; in[1] += value; in[2] += value; in[3] += value;
                in[4] += value; in[5] += value; in[6] += value; in[7] += value;
            }
            for(size_t i = size&7; i; --i, in++)
            {
                in[0] += value;
            }
        }
        
        //! Adds a scalar to a vector and leaves the result in another.
        /** Adds a scalar to a vector and leaves the result in another.
         @param size  The size of the vectors.
         @param value The value.
         @param in    The vector.
         @param out   The output vector.
         */
        static inline void add(const size_t size, T const& value, const T* in, T* out) noexcept
        {
            for(size_t i = size>>3; i; --i, in += 8, out += 8)
            {
                out[0] = value + in[0]; out[1] = value + in[1]; out[2] = value + in[2]; out[3] = value + in[3];
                out[4] = value + in[4]; out[5] = value + in[5]; out[6] = value + in[6]; out[7] = value + in[7];
                
            }
            for(size_t i = size&7; i; --i, in++, out++)
            {
                out[0] += value + in[0];
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
