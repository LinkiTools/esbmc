/*
 * clang_c_main.h
 *
 *  Created on: Jul 29, 2015
 *      Author: mramalho
 */

#ifndef CLANG_C_FRONTEND_CLANG_MAIN_H_
#define CLANG_C_FRONTEND_CLANG_MAIN_H_

#include <context.h>
#include <message.h>
#include <std_code.h>

bool clang_main(
  contextt &context,
  const std::string &default_prefix,
  const std::string &standard_main,
  message_handlert &message_handler);

#endif /* CLANG_C_FRONTEND_CLANG_MAIN_H_ */
