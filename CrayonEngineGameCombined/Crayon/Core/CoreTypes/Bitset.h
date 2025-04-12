#pragma once
#include"Core.h"

namespace Crayon
{
    //mimics and replaces std::bitset, but gives you an iterator that lets you iterate over all the set bits in a bitset.
    //It is an array of uint64_ts. If the bitset size isn't a multiple of 64 that's fine: you're not allowed to touch any of the bits outside of NUM_BITS anyway.
    template<size_t NUM_BITS>
    class Bitset
    {
        inline static constexpr size_t BITS_PER_WORD = sizeof( uint64_t ) * 8;
        
        
        //LEARN
        //I know this is basic but I never thought of doing it: normally I'd end up casting to floats, rounding up to the nearest int etc., which would be v. wasteful!
        inline static constexpr size_t NUMBER_OF_WORDS = (NUM_BITS + BITS_PER_WORD - 1) / BITS_PER_WORD;
        std::array<uint64_t, NUMBER_OF_WORDS> m_bits{};


    public:

        void getPosition( size_t bitPosition, size_t& wordPosition, size_t& bitOffset ) const
        {
            wordPosition = bitPosition / BITS_PER_WORD;
            bitOffset = bitPosition % BITS_PER_WORD;
        }


        void set( size_t position )
        {
            CRAYON_ASSERT( position < NUM_BITS );
            size_t wordPosition, bitOffset;
            getPosition( position, wordPosition, bitOffset );

            m_bits[wordPosition] |= (1ULL << bitOffset);
        }


        void set( size_t position, bool bitValue)
        {
            if ( bitValue )
            {
                set( position );
            }
            else
            {
                reset( position );
            }
        }


        void reset( size_t position )
        {
            CRAYON_ASSERT( position < NUM_BITS );
            size_t wordPosition, bitOffset;
            getPosition( position, wordPosition, bitOffset );

            //LEARN: not (0ULL<<bitOffset)! That... wld just move a 0 into a big bunch of 0s!
            m_bits[wordPosition] &= ~(1ULL << bitOffset);
        }


        bool test( size_t position ) const
        {
            CRAYON_ASSERT( position < NUM_BITS );

            size_t wordPosition, bitOffset;
            getPosition( position, wordPosition, bitOffset );

            return m_bits[wordPosition] & (1ULL << bitOffset);
        }


        void clear()
        {
            for ( auto& word : m_bits )
            {
                word = 0;
            }
        }

        
        //LEARN
        //Exposing the wiring (not pushing down adding the 1 etc. into the lower functions) really made all of this a lot nicer and clearer.
        //Leave dealing with the fiddly bits to the end,and handle the fiddliness whenever possible in the caller, not the callee.
        size_t findNextSetBitInBitset( size_t currentPosition )
        {
            return findLowestSetBitInBitset( currentPosition + 1 );
        }

        size_t findLowestSetBitInBitset( size_t currentPosition=0 )
        {
            size_t wordPosition, bitOffset;
            getPosition( currentPosition, wordPosition, bitOffset );

            for ( size_t i = wordPosition; i < m_bits.size(); i++ )
            {
                if ( uint64_t shiftedWord = m_bits[i] >> bitOffset )
                {
                    size_t nextSetBit = findLowestSetBitInWord( shiftedWord );
                    if ( nextSetBit != NUM_BITS )
                    {
                        return nextSetBit + (i * BITS_PER_WORD) + bitOffset;
                    }
                }
                bitOffset = 0;
            }
            return NUM_BITS;
        }



        size_t findLowestSetBitInWord( uint64_t word )
        {
            uint64_t isolatedNextBit =( (~word) + 1 )  &   (word);
            return (int)log2( isolatedNextBit );
        }

        class Iterator
        {
            Bitset& m_bitset;
            size_t m_position = 0;

        public:
            Iterator(Bitset& bitset, size_t position): m_bitset(bitset), m_position(position){}

            size_t operator*() const { return m_position; }

            Iterator& operator++() 
            {
                m_position = m_bitset.findNextSetBitInBitset( m_position );
                return *this;
            }

            Iterator operator++( int )
            {
                Iterator temp = *this;
                ++(*this);
                return temp;
            }

            bool operator==(const Iterator& other )
            {
                return m_position == other.m_position;
            }

            bool operator!=( const Iterator& other )
            {
                return m_position != other.m_position;
            }

        };

        //this is for our non-const Bitset::[] operator to be able to return something: myBitset[0]=true; needs to return something that can assign true to the 0th bit. We can't return a reference to the actual bit, because the smallest memory address is a byte, and we can't return a reference to the Bitset itself, because myBitset=true doesn't mean anyting, so we return a wrapper class around the Bitset that knows what bit we're dealing with and will let you set or unset that specific bit.
        class BitWrapper
        {
            Bitset& m_bitset;
            size_t m_bit;
        public:
            BitWrapper(Bitset& bitset, size_t bit):m_bitset(bitset), m_bit(bit){}

            //LEARN
            //yes, you could just return a bool, but it's a bit of a weird thing to do! It's standard practice for the assignment operator to return a reference to the object so that you can have chains
            BitWrapper& operator=( bool newValue )
            {
                if ( newValue )
                {
                    m_bitset.set( m_bit );
                }
                else
                {
                    m_bitset.reset( m_bit );
                }
                return *this;
            }

         //LEARN: conversion operators: they have no return type (because they overlap with constructors and use the same syntax), and we pretend that the "operator" is the name of the type that you're casting to
            operator bool() const
            {
                return m_bitset.test( m_bit );
            }
        };
       
        Iterator begin()
        {
           return Iterator( *this, findLowestSetBitInBitset() );
        }

        Iterator end()
        {
           return Iterator( *this, NUM_BITS );
        }

        Bitset& operator=( const Bitset& other )
        {
            for ( size_t i = 0; i < m_bits.size(); i++ )
            {
                m_bits[i] = other.m_bits[i];
            }
            return *this;
        }

        bool operator==( const Bitset& other ) const
        {
            for ( size_t i=0;i<m_bits.size();i++ )
            {
                if ( m_bits[i] != other.m_bits[i] )
                {
                    return false;
                }
            }
            return true;
        }

        bool operator!=( const Bitset& other ) const
        {
            return !(*this == other);
        }
        
        Bitset operator~() const
        { 
            Bitset newBitset =*this;
            for ( auto& word : newBitset.m_bits )
            {
                word = ~word;
            }
            return newBitset;
        }

        Bitset operator&( const Bitset& other ) const
        {
            Bitset newBitset = *this;
            for ( size_t i = 0; i < newBitset.m_bits.size(); i++ )
            {
                newBitset.m_bits[i] &= other.m_bits[i];
            }
            return newBitset;
        }

        //LEARN: these operator COMBINATIONS are NOT auto-generated for you out of the other operators you have defined: you have to do them manually!
        Bitset& operator&=( const Bitset& other )
        {
            for ( size_t i = 0; i < other.m_bits.size(); i++ )
            {
                m_bits[i] &= other.m_bits[i];
            }
            return *this;
        }

        Bitset operator|(const Bitset& other) const
        {
            Bitset newBitset=*this;
            for ( size_t i = 0; i < newBitset.m_bits.size(); i++ )
            {
                newBitset.m_bits[i] |= other.m_bits[i];
            }
            return newBitset;
        }

        Bitset& operator|=( const Bitset& other )
        {
            for ( size_t i = 0; i < m_bits.size(); i++ )
            {
                m_bits[i] |= other.m_bits[i];
            }
            return *this;
        }

        //LEARN:
        // bool foo = myBitset[3] will give you the const version, and bool foo = myBitset[3]=false will give you the non-const version.
        //It's notable that what tips C++ off as to what version to use isn't actually that one version is const and the other isn't: rather, it's the fact that one returns an lvalue (that can have a value assigned to it) and one returns an r-value (that can). But in any case, the const overloading here lets us have 2 separate [] signatures to choose from!
        bool operator[]( size_t index ) const
        {
            return test( index );
        }

        //LEARN
        BitWrapper operator[]( size_t index )
        {
            CRAYON_ASSERT( index < NUM_BITS );
            BitWrapper bitWrapper( *this, index );
            return bitWrapper;
        }

    };


}