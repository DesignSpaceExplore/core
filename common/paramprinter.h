// vim : set fileencoding=utf-8 expandtab noai ts=4 sw=4 :
/// @addtogroup common
/// @{
/// @file paramprinter.h
/// 
///
/// @date 2010-2014
/// @copyright All rights reserved.
///            Any reproduction, use, distribution or disclosure of this
///            program, without the express, prior written consent of the 
///            authors is strictly prohibited.
/// @author Timo Veit
///

#include "greencontrol/config.h"
#include "gs_config/propertyconfig.h"

class paramprinter {
  public:
    	paramprinter();
    	~paramprinter();
		void printParams();
		void printParams(std::string key);
		void printConfigs();
		void printConfigs(std::string key);

	private:
		gs::cnf::cnf_api* mApi;

};
/// @}