#include "EngineFiles.h"

const std::string EngineFiles::RES_FOLDER = GetWorkingDirectory::GetCurrentWorkingDir() + "\\res\\";
const std::string EngineFiles::ERROR_FOLDER = GetWorkingDirectory::GetCurrentWorkingDir() + "\\ErrorLogs\\";

const std::string EngineFiles::GUI_FOLDER = RES_FOLDER + "\\GUIs\\";
const std::string EngineFiles::FONT_FOLDER = RES_FOLDER + "\\fonts";
const std::string EngineFiles::DEFAULT_FONT_ATLAS = FONT_FOLDER + "\\default.png";
const std::string EngineFiles::DEFAULT_FONT_META = FONT_FOLDER + "\\default.fnt";
const std::string EngineFiles::ICON_FOLDER = RES_FOLDER + "\\windowIcon\\";
const std::string EngineFiles::LANG_FILE = RES_FOLDER + "\\languageFile.csv";