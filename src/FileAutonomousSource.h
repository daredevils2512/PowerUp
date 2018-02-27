/*
 * FileAutonomousSource.h
 *
 *  Created on: Feb 20, 2018
 *      Author: noahg
 */

#ifndef SRC_FILEAUTONOMOUSSOURCE_H_
#define SRC_FILEAUTONOMOUSSOURCE_H_

#include <string>
#include "AutonomousSource.h"

class FileAutonomousSource :  public AutonomousSource {
public:
	FileAutonomousSource(std::string filename);
	virtual ~FileAutonomousSource();
};

#endif /* SRC_FILEAUTONOMOUSSOURCE_H_ */

