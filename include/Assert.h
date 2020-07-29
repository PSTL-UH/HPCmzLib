#include <iostream>
#include <optional>
//Added include statements
#include <vector>

class Assert {
public:
    template<class T>
    static void AreEqual(T a, T b ) {
        if ( a==b ){
//            std::cout << "is equal" << std::endl;
        }
        else {
            std::cout << "  Assert.h: " << a << " is NOT equal " << b << std::endl;
//            std::abort();
        }
    }

    template<class T1, class T2>
    static void AreEqual(T1 a, T2 b ) {
        if ( a==b ){
//            std::cout << "is equal" << std::endl;
        }
        else {
            std::cout << "  Assert.h: " << a << " is NOT equal " << b << std::endl;
//            std::abort();
        }
    }

    static void AreEqual(double a, std::optional<double> b) {
        if ( b.has_value() ) {
            if ( a==b.value() ){
//            std::cout << "is equal" << std::endl;                
            }
        }
        std::cout << "  Assert.h: " << a << " is NOT equal " << b.value() << std::endl;
        //   std::abort();        
    }

    template<class T>
    static void AreEqual(T a, T b, double tol ) {
        if ( std::abs(a-b) <tol ) {
//            std::cout << "is equal" << std::endl;
        }
        else {
            std::cout << "  Assert.h: " << a << " is NOT equal " << b << "within " << tol << std::endl;
//            std::abort();
        }
    }
    static void AreEqual (char *a, std::string s) {
        std::string s2=a;
        if ( s == s2 ) {
//            std::cout << "is equal" << std::endl;
        }
        else {
            std::cout << "  Assert.h: " << a << " is NOT equal " << s << std::endl;
//            std::abort();
        }
    }
    
    template<class T>
    static void AreNotEqual(T a, T b ) {
        if ( a!=b ){
//            std::cout << "is not equal" << std::endl;
        }
        else {
            std::cout << "  Assert.h: " << a << " is EQUAL but should not be " << b << std::endl;
//            std::abort();
        }
    }

    template<class T1, class T2>
    static void AreNotEqual(T1 a, T2 b ) {
        if ( a!=b ){
//            std::cout << "is not equal" << std::endl;
        }
        else {
            std::cout << "  Assert.h: " << a << " is EQUAL but should not be " << b << std::endl;
//            std::abort();
        }
    }

    static void IsTrue ( bool a) {
        if ( !a ) {
            std::cout << "  Assert.h: is FALSE but should be TRUE" << std::endl;
//            std::abort();
        }
    }
    static void IsFalse ( bool a) {
        if ( a ) {
            std::cout << "  Assert.h: is TRUE but should be FALSE" << std::endl;
//            std::abort();
        }
    }
    template <class T>
    static void IsNull ( T a) {
        if ( a != nullptr ) {
            std::cout << "  Assert.h: is not NULL but should be"  << std::endl;
//            std::abort();
        }
    }
    
    //  static void Throws ( T a1);


    template <class T>
    static bool SequenceEqual ( std::vector<T> a, std::vector<T> b ) {
        if ( a.size() != b.size() ) {
            return false;
        }

        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());
        return std::equal(a.begin(), a.end(), b.begin());                
    }

};
