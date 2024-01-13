#pragma once

template<typename T>
class KGlobalSingleton
{
public:
    using Type          = Type;
    inline static Type& Singleton() { return KSingletonCreator::Access(); }
    inline              KGlobalSingleton() {}

private:
                        KGlobalSingleton( const KGlobalSingleton& );
                        KGlobalSingleton& operator=( const KGlobalSingleton& );

protected:
    class KSingletonCreator
    {
    public:
        inline KSingletonCreator()
        {
            Access();
        }//KSingletonCreator()

        inline static Type& Access()
        {
            /* ref 는 처음 1번만 _NoInlineAccess() 호출을 통해 초기화되고
             * 이후 Access() 호출은 inline 화 되어 사용된다. */
            static  Type&  ref = _NoInlineAccess();
            return  ref;
        }//Access()

    private:
        __declspec( noinline ) static Type& _NoInlineAccess()
        {
            static Type obj;
            ms_kSingletonCreator;
            return obj;
        }//_NoInlineAccess()

    private:
        static KSingletonCreator    ms_kSingletonCreator;
    };//struct KSingletonCreator
};//template<typename T>

template <typename T>
/*static*/ typename KGlobalSingleton<T>::KSingletonCreator  KGlobalSingleton<T>::KSingletonCreator::ms_kSingletonCreator;
