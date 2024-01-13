#pragma once

template<typename T>
class KGlobalSingletonNotGood
{
public:
    using Type          = Type;
    inline static Type& Singleton() { return KSingletonCreator::Access(); }
    inline              KGlobalSingletonNotGood() {}

private:
                        KGlobalSingletonNotGood(const KGlobalSingletonNotGood&);
                        KGlobalSingletonNotGood& operator=(const KGlobalSingletonNotGood&);

protected:
    class KSingletonCreator
    {
    public:
        inline KSingletonCreator()
        {
            Access();
        }//KSingletonCreator()

        __declspec(noinline) static Type& Access()
        {
            /* ref 는 처음 1번만 초기화되긴 하지만
             * 접근하기 위해서는 매번 inline 이 아닌 Access() 호출을 통해 접근해야 한다. */
            static Type ref;
            ms_kSingletonCreator;
            return ref;
        }//Access()

    private:
        static KSingletonCreator    ms_kSingletonCreator;
    };//class KSingletonCreator
};

template <typename T>
/*static*/ typename KGlobalSingletonNotGood<T>::KSingletonCreator
KGlobalSingletonNotGood<T>::KSingletonCreator::ms_kSingletonCreator;
