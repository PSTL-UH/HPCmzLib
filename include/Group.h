#include <functional>
#include <vector>

class Group {
public:
    template <typename T1>
        static std::vector<std::vector<T1>> GroupBy( std::vector<T1> invec,
                                                     std::function<bool(T1, T1)> func1,
                                                     std::function<bool(T1, T1)> func2)
    {
        std::vector<T1> vec( invec.begin(),  invec.end());
        std::sort(vec.begin(), vec.end(), [&] (T1 l, T1 r) { return func1(l,r); } );
        std::vector<std::vector<T1>> resvecs;

        int current = 0;
        for ( auto p = vec.begin(); p != vec.end(); p ++ ) {
            if ( p == vec.begin() ) {
                std::vector<T1> *v = new  std::vector<T1>;
                resvecs.push_back (*v);
            }
            else {
                auto q = p -1;
                if ( func2(*p, *q) ) {
                    std::vector<T1> *v = new  std::vector<T1>;
                    resvecs.push_back (*v);
                    current++;
                }
            }
            resvecs[current].push_back(*p);
        }
        return resvecs;
    }
};
