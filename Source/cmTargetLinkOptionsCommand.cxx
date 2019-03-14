/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#include "cmTargetLinkOptionsCommand.h"

#include <sstream>

#include "cmAlgorithms.h"
#include "cmListFileCache.h"
#include "cmMakefile.h"
#include "cmMessageType.h"
#include "cmTarget.h"

class cmExecutionStatus;

bool cmTargetLinkOptionsCommand::InitialPass(
  std::vector<std::string> const& args, cmExecutionStatus&)
{
  return this->HandleArguments(args, "LINK_OPTIONS", PROCESS_BEFORE);
}

void cmTargetLinkOptionsCommand::HandleMissingTarget(const std::string& name)
{
  std::ostringstream e;
  e << "Cannot specify link options for target \"" << name
    << "\" which is not built by this project.";
  this->Makefile->IssueMessage(MessageType::FATAL_ERROR, e.str());
}

std::string cmTargetLinkOptionsCommand::Join(
  const std::vector<std::string>& content)
{
  return cmJoin(content, ";");
}

bool cmTargetLinkOptionsCommand::HandleDirectContent(
  cmTarget* tgt, const std::vector<std::string>& content, bool prepend, bool)
{
  cmListFileBacktrace lfbt = this->Makefile->GetBacktrace();
  tgt->InsertLinkOption(this->Join(content), lfbt, prepend);
  return true; // Successfully handled.
}
