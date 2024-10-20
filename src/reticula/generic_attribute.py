import typing as _typing
import collections


class generic_attribute(collections.abc.Mapping):
    def __init__(
            self, attr_prefix: str,
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
                    f"Provided template type {str(keys)} is not a valid "
                    "option. Valid options are:\n\n" +
                    self.options_list())
        return self.function_module.__getattribute__(attr_name)

    def options_list(self):
        opts = []
        for type_list in self.options:
            opts.append(
                "[" + ", ".join([t.__class_name__() for t in type_list]) + "]")
        opts = sorted(opts, key=lambda s: (s.count("["), s))

        return "\n".join(opts)

    def __call__(self, *args, **kwargs):
        raise TypeError(
           "No type information was paased to a generic function or type.\n"
           "This usually means that you forgot to add square brackets\n"
           "and type information before parentheses, e.g.:\n\n"
           f"    {self.api_module_name}.{self.attr_prefix}"
           f"[{', '.join(self.arg_names)}]"
           "\n\nValid options are:\n\n" + self.options_list())

    def __repr__(self) -> str:
        return f"{self.api_module_name}.{self.attr_prefix}"\
            f"[{", ".join(self.arg_names)}]"

    def __len__(self) -> int:
        return len(self.options)

    def __iter__(self):
        return iter(self.options)
