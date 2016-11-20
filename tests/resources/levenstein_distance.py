from subprocess import call, Popen, check_output
from robot.libraries.BuiltIn import BuiltIn
from robot.api.deco import keyword
from re import findall


_get_robot_var = BuiltIn().get_variable_value
_log = BuiltIn().log
_log_to_console = BuiltIn().log_to_console
_output_results_regex = r'\(([\w\d]*)\s*\,\s*([\w\d]*)\)\s*\=\s*(\d*)'
_get_executable_output = lambda *args: check_output([
                _get_robot_var('${APP_EXECUTABLE_NAME}'),
] + args).decode('utf-8')
_parse_robot_list = lambda x: x.split(', ')


@keyword('levenstein distance equals')
def application_returns(arg1, arg2, r):
    _log_to_console('checking if LD({}, {}) = {}'.format(arg1, arg2, r))
    output = _get_executable_output(arg1, arg2)
    temp = findall(_output_results_regex , output)
    BuiltIn().should_be_true((arg1, arg2, r) in temp)


@keyword('check file reading capabilities')
def kw2(words, lengths):
    with open(_get_robot_var('${DEFAULT_INPUT_FILENAME}'), mode='w') as fp:
        fp.writelines(_parse_robot_list(words))
    res = _get_executable_output(

