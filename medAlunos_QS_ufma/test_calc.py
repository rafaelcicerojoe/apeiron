import pytest
import string
from io import StringIO
import _modules.calcMedia as calcula


def test_menor():
    assert calcula.getMenorEntre4(5, 4, 4, 3) == True
    pass

def test_input():
    assert calcula.verifyInput('a') !=False
    pass

def test_med(capsys):
    calcula.getMedia(10,12,20)
    captured_stdout, captured_stderr = capsys.readouterr()
    assert captured_stdout.strip() == 'undef'