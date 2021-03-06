/*
 * loopst.h
 *
 *  Created on: Jun 30, 2015
 *      Author: mramalho
 */

#ifndef GOTO_PROGRAMS_GOTO_LOOPS_H_
#define GOTO_PROGRAMS_GOTO_LOOPS_H_

#include <std_types.h>
#include <hash_cont.h>

#include <message_stream.h>

#include "goto_functions.h"
#include "loopst.h"

class goto_loopst : public message_streamt
{
public:
  goto_loopst(
    contextt &_context,
    const irep_idt &_function_name,
    goto_functionst &_goto_functions,
    goto_functiont &_goto_function,
    message_handlert &_message_handler) :
    message_streamt(_message_handler),
    context(_context),
    function_name(_function_name),
    goto_functions(_goto_functions),
    goto_function(_goto_function)
  {
    find_function_loops();
  }

  void find_function_loops();
  void dump();

protected:
  contextt &context;
  const irep_idt function_name;
  goto_functionst &goto_functions;
  goto_functiont &goto_function;

  typedef std::list<loopst> function_loopst;
  function_loopst function_loops;

  void create_function_loop(
    goto_programt::instructionst::iterator loop_head,
    goto_programt::instructionst::iterator loop_exit);

  void get_modified_variables(
    goto_programt::instructionst::iterator instruction,
    function_loopst::iterator loop,
    const irep_idt &_function_name);

  void add_loop_var(loopst &loop, const exprt &expr);
};

#endif /* GOTO_PROGRAMS_GOTO_LOOPS_H_ */
