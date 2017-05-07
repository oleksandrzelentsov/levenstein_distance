from subprocess import call, Popen, check_output
from robot.libraries.BuiltIn import BuiltIn
from robot.api.deco import keyword
from re import findall
from itertools import combinations
from os.path import isfile


_get_robot_var = BuiltIn().get_variable_value
_log = BuiltIn().log
_log_to_console = BuiltIn().log_to_console
_output_results_regex = r'\|[\s\W]*([\w\d]*)[\s\W]*([\w\d]*)[\s\W]*(\d*)'
_get_executable_output = lambda *args: check_output([
                _get_robot_var('${APP_EXECUTABLE_NAME}'),
] + list(args)).decode('utf-8')
_parse_robot_list = lambda x: list(map(lambda y: y + '\n', x.split(', ')))


def _check_if_output_has(output, *data):
    temp = findall(_output_results_regex, output)
    for arg1, arg2, r in data:
        BuiltIn().should_be_true((arg1, arg2, r) in temp or (arg2, arg1, r) in temp)


@keyword('levenstein distance equals')
def application_returns(arg1, arg2, r):
    _log_to_console('checking if LD({}, {}) = {}'.format(arg1, arg2, r))
    output = _get_executable_output(arg1, arg2)
    _check_if_output_has(output, (arg1, arg2, r))


def _check_file_reading(words, filename):
    words = _parse_robot_list(words)
    with open(filename, mode='w') as fp:
        fp.writelines(words)
    res = _get_executable_output('--filename', filename)
    list_ = findall(_output_results_regex, res)
    _log_to_console('matches: {}'.format(str(list_)))
    _log_to_console('length should be: {}'.format(len(list(combinations(words, 2)))))
    BuiltIn().length_should_be(list_, len(list(combinations(words, 2))), 'different lengths of input and output\noutput:\n{}'.format(res))
    for arg1, arg2, r in list_:
        application_returns(arg1, arg2, r)


@keyword('check file reading capabilities')
def kw2(words):
    _check_file_reading(words,
                        filename=_get_robot_var('${DEFAULT_INPUT_FILENAME}'))


@keyword('backup current input file')
def setup_mine():
    _log_to_console('| TESTING |')
    filename = _get_robot_var('${DEFAULT_INPUT_FILENAME}')
    if isfile(filename):
        call(['mv', filename, filename + '.bak'])


@keyword('restore current input file')
def teardown_mine():
    filename = _get_robot_var('${DEFAULT_INPUT_FILENAME}')
    if isfile(filename + '.bak'):
        call(['mv', filename + '.bak', filename])
    elif isfile(filename):
        call(['rm', filename])
