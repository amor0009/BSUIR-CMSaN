#ifndef CONFIG_H
#define CONFIG_H

#define TITLE "find CURSES"
#define VERSION "v1.0"
#define DESCRIPTION "This program is a simple shell over the find utility. Nicetrym8 was developed as a course work on the discipline of OSiSP. Distributed under the MIT license (https://mit-license.org /). Copyright (c) 2023 Nicetrym8."
//Название меток для UI
#define FILE_TYPE_GUI "Display files"
#define DIR_TYPE_GUI "Display catalogs"
#define SYMLINK_TYPE_GUI "Display symbolic links"
#define EXECUTE_GUI "Perform"
#define ADDITIONAL_COMMAND_GUI "Parameters"
#define ABOUT_GUI "About programm"
#define SEARCH_GUI "Search"
#define REGEXP_GUI "Regular expression"
#define NAME_GUI "Name format"
#define GROUP_GUI "Group"
#define PERM_GUI "Access"
#define SIZE_GUI "File size"
#define USER_GUI "User"
#define QUERY_STRING_GUI "Request format"
#define EXIT_GUI "Exit/Back"

#define name_and_version_str(name, version) name " " version
#define PROGRAM_NAME name_and_version_str(TITLE,VERSION)

#define SETTINGS_PATH "./userdata"
#define VISIBLE_MAX 1024
#endif