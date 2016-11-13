from subprocess import call, Popen, check_output
from robot.libraries.BuiltIn import BuiltIn
from robot.api.deco import keyword
from re import findall


_get_robot_var = BuiltIn().get_variable_value
_log = BuiltIn().log
_log_to_console = BuiltIn().log_to_console


@keyword('levenstein distance equals')
def application_returns(arg1, arg2, r):
    _log_to_console('checking if LD({}, {}) = {}'.format(arg1, arg2, r))
    output = (check_output([_get_robot_var('${APP_EXECUTABLE_NAME}'), arg1, arg2])).decode('utf-8')
    output = output.replace(' ', '').replace('\n', '')
    temp = findall(r'\(([\w\d]*)\,([\w\d]*)\)\=(\d*)', output)
    BuiltIn().should_be_true((arg1, arg2, r) in temp)


@keyword('check file reading capabilities')
def kw2(words, lengths):
    with open(_get_robot_var('${DEFAULT_INPUT_FILENAME}')) as fp:
        fp.writelines(words.split(', '))

