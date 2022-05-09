import itertools as _itertools
import typing as _typing

from . import reticula_ext as _reticula_ext

class generic_attribute:
    def __init__(self, attr_prefix: str,
            arg_names: _typing.Tuple[str, ...],
            options: _typing.Iterable[_typing.Tuple[type, ...]],
            function_module, api_module_name):
        self.options = set(options)
        self.attr_prefix = attr_prefix
        self.arg_names = arg_names
        self.function_module = function_module
        self.api_module_name = api_module_name
    def __getitem__(self, keys):
        if not isinstance(keys, tuple):
            keys = (keys,)

        if len(keys) != len(self.arg_names):
            raise AttributeError(
                f"Wrong number of type templates: expected "
                f"{len(self.arg_names)} template types but received "
                f"{len(keys)}.\nThe expected template types are "
                f"[{', '.join(self.arg_names)}]")

        attr_name = str(self.attr_prefix)
        if not self.options or keys in self.options:
            attr_name = str(self.attr_prefix) + "_" + \
                "_".join([k.__name__ for k in keys])
        else:
            raise AttributeError(
                    f"Provided template type is not a valid "
                    f"option. Valid options are:\n" + "\n".join(
                    ["\t["+", ".join([t.__name__ for t in type_list]) +"]"
                        for type_list in self.options]))
        return self.function_module.__getattribute__(attr_name)
    def __call__(self, *args, **kwargs):
        raise TypeError(
           "No type information was paased to a generic function or type.\n"
           "This usually means that you forgot to add square brackets\n"
           "and type information before parentheses, e.g.:\n\n"
           f"    {self.api_module_name}.{self.attr_prefix}"
           f"[{', '.join(self.arg_names)}]"
           "\n\nValid options are:\n\n" + "\n".join(
               ["    ["+", ".join([t.__name__ for t in type_list]) +"]"
                   for type_list in self.options]))
