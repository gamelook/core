// Copyright 2010 By chenxianchuang. All rights reserved.
/*! @file
	@brief Application¿‡∂®“Â
	@author chenxianchuang
*/

/** The author disclaims copyright to this source code.  In place of
	** a legal notice, here is a blessing:
    **
	**    May you do good and not evil.
	**    May you find forgiveness for yourself and forgive others.
	**    May you share freely, never taking more than you give.
*/

#ifndef CORE_CORE_APPLICATION_H__
#define CORE_CORE_APPLICATION_H__

#include <stdio.h>

namespace core
{


class Application
{
public:
	Application();
	virtual ~Application();

	void run(int argc=0, char* argv[]=NULL);

	virtual void onInit(int argc, char* argv[]) = 0;
	virtual void onSave() = 0;
	virtual void onExit() = 0;

private:

};

}

#endif //CORE_CORE_APPLICATION_H__
