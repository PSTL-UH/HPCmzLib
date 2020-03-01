#pragma once

#include <vector>
#include <iostream>

namespace FlashLFQ
{
    class Elementwise {
    public:
        static std::vector<double> Add ( std::vector<int> &a, double &b){
            std::vector<double>result(a.size());
            for ( unsigned int i = 0; i< a.size(); i++ ){
                result[i] = (double)a[i] + b;
            }
            return result;
        }

        static std::vector<double> Add ( std::vector<double> &a, double &b){
            std::vector<double>result(a.size());
            for ( unsigned int i = 0; i< a.size(); i++ ){
                result[i] = a[i] + b;
            }
            return result;
        }
        static std::vector<double> Add ( std::vector<double> &a, std::vector<double> &b){
            if ( a.size() != b.size() ) {
                std::cout << "Mismatching vector sizes in Elementwise::Add\n";
            }
            std::vector<double>result(a.size());
            for ( unsigned int i = 0; i< a.size(); i++ ){
                result[i] = a[i] + b[i];
            }
            return result;
        }

        static std::vector<double> Subtract ( double &a, std::vector<double> &b){
            std::vector<double>result(b.size());
            for ( unsigned int i = 0; i< b.size(); i++ ){
                result[i] = a - b[i];
            }
            return result;
        }

        static std::vector<double> Subtract ( std::vector<double> &a, std::vector<double> &b){
            if ( a.size() != b.size() ) {
                std::cout << "Mismatching vector sizes in Elementwise::Subtract\n";
            }
            std::vector<double>result(a.size());
            for ( unsigned int i = 0; i< a.size(); i++ ){
                result[i] = a[i] - b[i];
            }
            return result;
        }

        static std::vector<double> Multiply ( std::vector<double> &a, double &b){
            std::vector<double>result(a.size());
            for ( unsigned int i = 0; i< a.size(); i++ ){
                result[i] = a[i] * b;
            }
            return result;
        }
        static std::vector<double> Multiply ( std::vector<double> &a, std::vector<double> &b){
            if ( a.size() != b.size() ) {
                std::cout << "Mismatching vector sizes in Elementwise::Multiply\n";
            }
            std::vector<double>result(a.size());
            for ( unsigned int i = 0; i< a.size(); i++ ){
                result[i] = a[i] * b[i];
            }
            return result;
        }

        static std::vector<double> Divide ( std::vector<double> &a, std::vector<double> &b){
            if ( a.size() != b.size() ) {
                std::cout << "Mismatching vector sizes in Elementwise::Divide\n";
            }
            std::vector<double>result(a.size());
            for ( unsigned int i = 0; i< a.size(); i++ ){
                result[i] = a[i] / b[i];
            }
            return result;
        }
    };
        
}
