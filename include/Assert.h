#include <iostream>

class Assert {
public:
    template<class T>
    static void AreEqual(T a, T b ) {
        if ( a == b )
            std::cout << "is equal" << std::endl;
        else {
            std::cout << "is NOT equal" << std::endl;
//            std::abort();
        }
    }

    static void IsTrue ( bool a) {
        if ( !a ) {
            std::cout << "is FALSE but should be TRUE" << std::endl;
            std::abort();
        }
    }
    static void IsFalse ( bool a) {
        if ( a ) {
            std::cout << "is TRUE but should be FALSE" << std::endl;
            std::abort();
        }
    }
    
    //  static void Throws ( T a1);
};
