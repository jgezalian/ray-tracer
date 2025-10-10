#include <ray_tracer/math/transform.h>

namespace ray_tracer::math {
    
Matrix translation(double x, double y, double z) {
    Matrix trans(Matrix::identity(4));
    trans(0, 3, x);
    trans(1, 3, y);
    trans(2, 3, z);

    return trans;
}

Matrix scaling(double x, double y, double z) {
    Matrix scale(Matrix::identity(4));
    scale(0, 0, x);
    scale(1, 1, y);
    scale(2, 2, z);

    return scale;
}

Matrix rotate_x(double r) {
    Matrix rot_x(Matrix::identity(4));
    rot_x(1, 1, std::cos(r));
    rot_x(1, 2, -1 * std::sin(r));
    rot_x(2, 1, std::sin(r));
    rot_x(2, 2, std::cos(r));

    return rot_x;
}

Matrix tuple_to_mat(const Tuple &t) {
    const Matrix t_col_mat = Matrix(4, 1, {t.x, t.y, t.z, t.w});
    return t_col_mat;
}

}  // namespace ray_tracer::math