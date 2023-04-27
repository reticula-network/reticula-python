#ifndef SRC_METACLASS_HPP_
#define SRC_METACLASS_HPP_

#include <pybind11/pybind11.h>

#include <string>
#include <fmt/format.h>

inline PyTypeObject* common_metaclass(const char* name) {
  PyTypeObject* base_metaclass =
    pybind11::detail::get_internals().default_metaclass;
  PyType_Slot slots[] = {
    {Py_tp_base, base_metaclass},
    {Py_tp_repr,  // call __class_repr__ when repr(type) is invoked
      (void*)+[](PyObject* self) -> PyObject* {
        return PyObject_CallMethod(self, "__class_repr__", nullptr);
      }},
    {0, nullptr},
  };
  PyType_Spec spec = {};
  spec.name = name;
  spec.basicsize = static_cast<int>(base_metaclass->tp_basicsize);
  spec.flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  spec.slots = slots;
  PyTypeObject* metaclass = (PyTypeObject*)PyType_FromSpec(&spec);
  if (!metaclass) throw pybind11::error_already_set();
  return metaclass;
}

#endif  // SRC_METACLASS_HPP_
