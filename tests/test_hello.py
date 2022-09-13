from template_python import hello_string


def test_hello_string():
    assert hello_string() == "Hello World!"
    assert hello_string("Case") == "Hello Case!"
