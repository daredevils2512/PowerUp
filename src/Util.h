/*
 * Util.h
 *
 *  Created on: Jan 12, 2018
 *      Author: Daredevils-Prog-1
 */

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

#include <string>

class Util {
	public:
		static void ReportError(std::string errorMessage);
		static void ReportWarning(std::string warningMessage);
};

#endif /* SRC_UTIL_H_ */
