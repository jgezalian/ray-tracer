#include <gtest/gtest.h>
#include "test_helpers.h"
#include <cmath>
#include <numbers>
#include <iostream>


constexpr double pi = 3.14159265358979323846;
using namespace ray_tracer::math;



TEST(Transform, translate_point){
    const Matrix trans = translation(5, -3, 2);
    const Tuple p = point(-3, 4, 5);
    const Matrix p_col_mat = Matrix(4, 1, {p.x, p.y, p.z, p.w});
    const Matrix p_trans_mat = trans * p_col_mat;
    const Tuple p_trans(p_trans_mat.data[0], p_trans_mat.data[1], p_trans_mat.data[2], p_trans_mat.data[3]);
    expect_tuple(p_trans, 2, 1, 7, 1);
}

TEST(Transform, translate_point_inv){
    const Matrix trans = translation(5, -3, 2);
    const Matrix trans_inv = inverse(trans);
    const Tuple p = point(-3, 4, 5);
    const Matrix p_col_mat = Matrix(4, 1, {p.x, p.y, p.z, p.w});
    const Matrix p_trans_mat = trans_inv * p_col_mat;
    const Tuple p_trans(p_trans_mat.data[0], p_trans_mat.data[1], p_trans_mat.data[2], p_trans_mat.data[3]);
    expect_tuple(p_trans, -8, 7, 3, 1);
}

TEST(Transform, translate_vector){
    const Matrix trans = translation(5, -3, 2);
    const Tuple v = vector(-3, 4, 5);
    const Matrix v_col_mat = Matrix(4, 1, {v.x, v.y, v.z, v.w});
    const Matrix v_trans_mat = trans * v_col_mat;
    const Tuple v_trans(v_trans_mat.data[0], v_trans_mat.data[1], v_trans_mat.data[2], v_trans_mat.data[3]);
    expect_tuple(v_trans, -3, 4, 5, 0);
}

TEST(Transform, scale_point){
   const Matrix scale = scaling(2, 3, 4);
    const Tuple p = point(-4, 6, 8);
    const Matrix p_col_mat = tuple_to_mat(p);
    const Matrix p_scale_mat = scale * p_col_mat;
    const Tuple p_scale(p_scale_mat.data[0], p_scale_mat.data[1], p_scale_mat.data[2], p_scale_mat.data[3]);
    expect_tuple(p_scale, -8, 18, 32, 1);
}

TEST(Transform, scale_vec){
    const Matrix scale = scaling(2, 3, 4);
    const Tuple v = vector(-4, 6, 8);
    const Matrix v_col_mat = tuple_to_mat(v);
    const Matrix v_trans_mat = scale * v_col_mat;
    const Tuple v_trans(v_trans_mat.data[0], v_trans_mat.data[1], v_trans_mat.data[2], v_trans_mat.data[3]);
    expect_tuple(v_trans, -8, 18, 32, 0);
}

TEST(Transform, scale_vec_inv){
    const Matrix scale = scaling(2, 3, 4);
    const Matrix scale_inv = inverse(scale);
    const Tuple v = vector(-4, 6, 8);
    const Matrix v_col_mat = tuple_to_mat(v);
    const Matrix v_trans_mat = scale_inv * v_col_mat;
    const Tuple v_trans(v_trans_mat.data[0], v_trans_mat.data[1], v_trans_mat.data[2], v_trans_mat.data[3]);
    expect_tuple(v_trans, -2, 2, 2, 0);
}

TEST(Transform, reflection){
    const Matrix scale = scaling(-1, 1, 1);
    const Tuple p = point(2, 3, 4);
    const Matrix p_col_mat = tuple_to_mat(p);
    const Matrix p_trans_mat = scale * p_col_mat;
    const Tuple p_trans(p_trans_mat.data[0], p_trans_mat.data[1], p_trans_mat.data[2], p_trans_mat.data[3]);
    expect_tuple(p_trans, -2, 3, 4, 1);
}

TEST(Transform, rotate_x) {
    const Tuple p = point(0, 1, 0);
    const Matrix half_quarter = rotate_x(pi/4);
    const Matrix full_quarter = rotate_x(pi/2);
    expect_tuple(half_quarter * p, 0, std::sqrt(2)/2, std::sqrt(2)/2, 1);
    expect_tuple(full_quarter * p, 0, 0, 1, 1);
}

TEST(Transform, rotate_inv_x) {
    const Tuple p = point(0, 1, 0);
    const Matrix half_quarter = rotate_x(pi/4);
    const Matrix inv_half_quarter = inverse(half_quarter);
    expect_tuple(inv_half_quarter * p, 0, std::sqrt(2)/2, -1 * std::sqrt(2)/2, 1);
}

