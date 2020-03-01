#pragma once


namespace FlashLFQ
{
    class Elementwise {
    public:
        static std::vector<double> Add ( std::vector<int> &a, double &b);        
        static std::vector<double> Add ( std::vector<double> &a, double &b);        
        static std::vector<double> Add ( std::vector<double> &a, std::vector<double> &b);        
        static std::vector<double> Subtract ( double &a, std::vector<double> &b);
        static std::vector<double> Subtract ( std::vector<double> &a, std::vector<double> &b);
        static std::vector<double> Multiply ( std::vector<double> &a, double &b);
        static std::vector<double> Multiply ( std::vector<double> &a, std::vector<double> &b);
        static std::vector<double> Divide ( std::vector<double> &a, std::vector<double> &b);
    };
        
}
