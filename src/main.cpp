#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
namespace py = pybind11;

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/python/pyapi.hpp>

PyObject * draw_rect(py::array in) {
    
    cv::Mat mat;
    
    if (!PyOpenCV_NdarrayToMat(in.ptr(), mat, "in"))
        return NULL;
    
    cv::Point pt1, pt2;
    pt1.x = 10;
    pt1.y = 10;
    pt2.x = 100;
    pt2.y = 100;
    
    rectangle(mat, pt1, pt2, cv::Scalar(255, 0, 0));
    
    return PyOpenCV_MatToNdarray(mat);
}


PYBIND11_PLUGIN(test_package) {
    
    
    py::module m("test_package");
    
    m.def("draw_rect", &draw_rect);

#ifdef VERSION_INFO
    m.attr("__version__") = py::str(VERSION_INFO);
#else
    m.attr("__version__") = py::str("dev");
#endif

    import_opencv();
    return m.ptr();
}
