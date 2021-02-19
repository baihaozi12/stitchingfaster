import stitchingfaster 

path_OK = [
    "/AI/baihao_82/C++2python_littlepussy_baihao/images/1.jpg",
    "/AI/baihao_82/C++2python_littlepussy_baihao/images/2.jpg",
    "/AI/baihao_82/C++2python_littlepussy_baihao/images/3.jpg",
    "/AI/baihao_82/C++2python_littlepussy_baihao/images/4.jpg"]

path_robot_1 = [
    "/AI/baihao_82/stitch_robot/1/1.png",
    "/AI/baihao_82/stitch_robot/1/2.png"]
path_ = [
    "/AI/baihao_82/stitch_robot/4/1.jpg",
    "/AI/baihao_82/stitch_robot/4/2.jpg",
    "/AI/baihao_82/stitch_robot/4/3.jpg",
    "/AI/baihao_82/stitch_robot/4/4.jpg",
    "/AI/baihao_82/stitch_robot/4/5.jpg",
    "/AI/baihao_82/stitch_robot/4/6.jpg",
    "/AI/baihao_82/stitch_robot/4/7.jpg",
    "/AI/baihao_82/stitch_robot/4/8.jpg",
    "/AI/baihao_82/stitch_robot/4/9.jpg"]
path_ = [
    "/AI/baihao_82/stitch_robot/1.jpg",
    "/AI/baihao_82/stitch_robot/2.jpg"]
path_taizi = [
    "/AI/baihao_82/stith_img_test/right/1.JPG",
    "/AI/baihao_82/stith_img_test/right/2.JPG",
    "/AI/baihao_82/stith_img_test/right/4.JPG",
    "/AI/baihao_82/stith_img_test/right/3.JPG"]

path_ = [
    "/AI/baihao_82/stitch_online_img/1/1.jpg",
    "/AI/baihao_82/stitch_online_img/1/2.jpg"]

path_ = [

    "/AI/baihao_82/stitch_online_img/3/1.jpg",
    "/AI/baihao_82/stitch_online_img/3/2.jpg",
    "/AI/baihao_82/stitch_online_img/3/3.jpg",
    "/AI/baihao_82/stitch_online_img/3/4.jpg",
    "/AI/baihao_82/stitch_online_img/3/5.jpg",
    "/AI/baihao_82/stitch_online_img/3/6.jpg",
    "/AI/baihao_82/stitch_online_img/3/7.jpg",
    "/AI/baihao_82/stitch_online_img/3/8.jpg",
    "/AI/baihao_82/stitch_online_img/3/9.jpg"]
import time
start_time = time.time()
out_path = "/AI/baihao_82/stitch_online_img/3/out.jpg"
out_path_box = "/AI/baihao_82/stitch_online_img/3/out_box.jpg"
result = stitchingfaster.stitching(path_,out_path)
end_time = time.time()
print("Total cost {}".format(str(end_time-start_time)))
import cv2
img1 = cv2.imread(out_path)

img__ = cv2.imread(path_[0])
h,w,_ = img__.shape

homo_inv_list = list()

for i in range(len(result)):
    # homo_inv = [
    #     [result[i].homo_inv_vector[0], result[i].homo_inv_vector[3], result[i].homo_inv_vector[6]],
    #     [result[i].homo_inv_vector[1], result[i].homo_inv_vector[4], result[i].homo_inv_vector[7]],
    #     [result[i].homo_inv_vector[2], result[i].homo_inv_vector[5], result[i].homo_inv_vector[8]]
    # ]

    homo_inv = [
        [result[i].homo_inv_vector[0], result[i].homo_inv_vector[1], result[i].homo_inv_vector[2]],
        [result[i].homo_inv_vector[3], result[i].homo_inv_vector[4], result[i].homo_inv_vector[5]],
        [result[i].homo_inv_vector[6], result[i].homo_inv_vector[7], result[i].homo_inv_vector[8]]
    ]
    homo_inv_list.append(homo_inv)

print(homo_inv_list)
point_size = 6
point_color_list = [(0, 0, 255), (0, 255, 0), (255, 0, 0), (0, 0, 0), (0, 0, 0),
                    (0, 255, 0),  (255, 0, 0), (0, 0, 255),(0, 255, 0),(0, 255, 0),
                    (0, 0, 255), (0, 255, 0), (255, 0, 0), (0, 0, 0), (0, 0, 0)]
point_color = (0, 0, 255) # BGR
thickness = 8 # 可以为 0 、4、8
import numpy as np
homo_inv_list = np.array(homo_inv_list)
def calculate_projection(_x_image, _y_image, homo_inv, shape_center_x,shape_center_y,proj_range_min_x ,proj_range_min_y,resolution_x, resolution_y):
    img_x_cx = _x_image - shape_center_x
    img_y_cy = _y_image - shape_center_y

    h_1_1 = homo_inv[0][0]
    h_1_2 = homo_inv[0][1]
    h_1_3 = homo_inv[0][2]

    h_2_1 = homo_inv[1][0]
    h_2_2 = homo_inv[1][1]
    h_2_3 = homo_inv[1][2]

    h_3_1 = homo_inv[2][0]
    h_3_2 = homo_inv[2][1]
    h_3_3 = homo_inv[2][2]

    _x_up = (h_1_2 * img_y_cy - h_2_2 * img_x_cx) * (h_2_3 - h_3_3 * img_y_cy) - (
                h_2_3 * img_x_cx - h_1_3 * img_y_cy) * (h_3_2 * img_y_cy - h_2_2)
    _x_down = (h_2_1 * img_x_cx - h_1_1 * img_y_cy) * (h_3_2 * img_y_cy - h_2_2) - (
                h_1_2 * img_y_cy - h_2_2 * img_x_cx) * (h_2_1 - h_3_1 * img_y_cy)

    _x = _x_up / _x_down
    _y = ((h_2_1 - h_3_1 * img_y_cy) * _x + (h_2_3 - h_3_3 * img_y_cy)) / (h_3_2 * img_y_cy - h_2_2)

    _x = (_x - proj_range_min_x) / resolution_x
    _y = (_y - proj_range_min_y) / resolution_y

    return _x,_y

for i in range(len(result)):
    resolution_x = result[i].resolution_x
    resolution_y = result[i].resolution_y
    proj_range_min_x = result[i].proj_range_min_x
    proj_range_min_y = result[i].proj_range_min_y
    shape_center_x = result[i].shape_center_x
    shape_center_y = result[i].shape_center_y
    homo_inv = homo_inv_list[i]
    point_color = point_color_list[i]

    point_1 = np.array([0, 0, 1])
    _x_image = point_1[0]
    _y_image = point_1[1]
    _ltop_x, _ltop_y = calculate_projection(_x_image, _y_image, homo_inv, shape_center_x, shape_center_y,
                                            proj_range_min_x,
                                            proj_range_min_y, resolution_x, resolution_y)
    # cv2.circle(img1, (int(_rbottom_x), int(_rbottom_y)), point_size, point_color, thickness)
    point_1 = np.array([w, 0, 1])
    _x_image = point_1[0]
    _y_image = point_1[1]
    _rtop_x, _rtop_y = calculate_projection(_x_image, _y_image, homo_inv, shape_center_x, shape_center_y,
                                            proj_range_min_x,
                                            proj_range_min_y, resolution_x, resolution_y)
    cv2.circle(img1, (int(_rtop_x), int(_rtop_y)), point_size, point_color, thickness)

    point_1 = np.array([0, h, 1])
    _x_image = point_1[0]
    _y_image = point_1[1]
    _lbottom_x, _lbottom_y = calculate_projection(_x_image, _y_image, homo_inv, shape_center_x, shape_center_y,
                                                  proj_range_min_x,
                                                  proj_range_min_y, resolution_x, resolution_y)
    cv2.circle(img1, (int(_lbottom_x), int(_lbottom_y)), point_size, point_color, thickness)

    point_1 = np.array([w, h, 1])
    _x_image = point_1[0]
    _y_image = point_1[1]
    _rbottom_x, _rbottom_y = calculate_projection(_x_image, _y_image, homo_inv, shape_center_x, shape_center_y, proj_range_min_x,
                                  proj_range_min_y, resolution_x, resolution_y)
    cv2.circle(img1, (int(_rbottom_x), int(_rbottom_y)), point_size, point_color, thickness)


    cv2.line(img1, (int(_lbottom_x), int(_lbottom_y)), (int(_ltop_x), int(_ltop_y)), point_color, thickness)
    cv2.line(img1, (int(_lbottom_x), int(_lbottom_y)), (int(_rbottom_x), int(_rbottom_y)), point_color, thickness)
    cv2.line(img1, (int(_rtop_x), int(_rtop_y)), (int(_ltop_x), int(_ltop_y)), point_color, thickness)
    cv2.line(img1, (int(_rtop_x), int(_rtop_y)), (int(_rbottom_x), int(_rbottom_y)), point_color, thickness)


cv2.imwrite(out_path_box,img1 )
