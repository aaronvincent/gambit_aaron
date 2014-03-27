//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  test functions implementations.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date Feb 2014
///
///  *********************************************

#ifndef __egg_box_hpp__
#define __egg_box_hpp__

#include <vector>
#include <algorithm>
#include <cmath>

#include "yaml_options.hpp"
#include "scanner_utils.hpp"
#include "priors.hpp"
#include "test_factory.hpp"
#include "test_functions/uniform.hpp"


namespace Gambit
{
        namespace Scanner_Testing
        {
                class EggBox : public Scanner::Function_Base
                {
                private:
                        std::vector <double> params;
                        std::vector<std::string> keys;
                        std::pair <double, double> length;
                        
                public:
                        //constructor defined in gaussian.cpp
                        EggBox (const Options &options) : params(2), keys(2)
                        {
                                keys[0] = "0";
                                keys[1] = "1";
                                
                                if (options.hasKey("length"))
                                {
                                        length = options.getValue<std::pair<double, double>> ("length");
                                }
                                else
                                {
                                        length = std::pair<double, double>(10.0, 10.0);
                                }
                        }
                        
                        const std::vector<std::string> &getKeys() const {return keys;}
                        const std::vector<double> &getParameters() const {return params;}
                        
                        double operator() (std::vector<double> &unit)
                        {
                                params[0] = unit[0]*length.first;
                                params[1] = unit[1]*length.second;
                                
                                return pow((2.0 + cos(params[0]*M_PI_2)*cos(params[1]*M_PI_2)), 5.0);
                        }
                        
                        ~EggBox(){}
                };
                
                LOAD_TEST_FUNCTOR(eggbox, EggBox)
        }
}

#endif