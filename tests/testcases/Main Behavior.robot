*** Settings ***
Library  levenstein_distance.py
Library  OperatingSystem

*** Variables ***
${DEFAULT_INPUT_FILENAME}  lwords.txt
${INPUT_FILENAME}          other.lwords.txt

*** Test cases ***
Basic functionality
    [Documentation]  Checks if the basic comparison works properly
    [Template]       Levenstein distance equals
    [Setup]          Log to Console  TESTING
    Jurek  Janek     2
    Marek  Marek     0
    Marek  Mareczek  3

File is located nearby, unmarked
    [Documentation]  Checks the situation when the file is in the folder but is not requested
    [Template]       Check file reading capabilities
    [Setup]          Log to Console  TESTING
    [Teardown]       Remove file  ${DEFAULT_INPUT_FILENAME}
    Jurek, Marek, Janek
