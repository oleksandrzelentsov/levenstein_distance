*** Settings ***
Library  levenstein_distance.py

*** Test cases ***
Basic functionality
    [Documentation]  Checks if the basic comparison works properly
    [Template]       Application returns
    [Setup]          Log to Console  TESTING
    Jurek  Janek     2
    Marek  Marek     0
    Marek  Mareczek  3
