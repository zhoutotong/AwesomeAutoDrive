#!/usr/bin/env python

import sys
sys.path.append('/home/tong/Documents/AwesomeAutoDrive/AwesomeViewer/ros_tools/devel/lib/python2.7/dist-packages')

import rospy
import time
from std_msgs.msg import Header
from rostopic import ROSTopicHz
from hmi_msgs.msg import node_state
from hmi_msgs.msg import all_state


from sensor_msgs.msg import Imu

from jsk_recognition_msgs.msg import BoundingBoxArray



hz_checker = ROSTopicHz(10, use_wtime=True)

msg_dict = {}
topic_keys = ['hz', 'hz_state', 'params']
param_keys = ['value', 'state']

pub = rospy.Publisher('sensor_status_node', all_state, queue_size = 10)

def func_checking_value(param, min, max):
	return param <= max and param >= min

def timer_callback(event):
	global hz_checker
	global pub

	node_msg = list()


	ret = hz_checker.get_hz('/imu/data')
	if(ret):
		if isinstance(ret, tuple) and len(ret) == 5:
			msg_dict['/imu/data']['hz'] = ret[0]
		else:
			msg_dict['/imu/data']['hz'] = -1
		msg_dict['/imu/data']['hz_state'] = func_checking_value(msg_dict['/imu/data']['hz'], 35.00, 40.00)

	ret = hz_checker.get_hz('/velodyne/bounding_boxes')
	if(ret):
		if isinstance(ret, tuple) and len(ret) == 5:
			msg_dict['/velodyne/bounding_boxes']['hz'] = ret[0]
		else:
			msg_dict['/velodyne/bounding_boxes']['hz'] = -1
		msg_dict['/velodyne/bounding_boxes']['hz_state'] = func_checking_value(msg_dict['/velodyne/bounding_boxes']['hz'], 9.00, 10.00)




	node_msg.append(node_state('/imu/data', 
					msg_dict['/imu/data']['hz'], 
					msg_dict['/imu/data']['hz_state'], 
					'header.seq', 
					msg_dict['/imu/data']['params']['header.seq']['value'], 
					msg_dict['/imu/data']['params']['header.seq']['state']))

	node_msg.append(node_state('/velodyne/bounding_boxes', 
					msg_dict['/velodyne/bounding_boxes']['hz'], 
					msg_dict['/velodyne/bounding_boxes']['hz_state'], 
					'boxes.length()', 
					msg_dict['/velodyne/bounding_boxes']['params']['boxes.length()']['value'], 
					msg_dict['/velodyne/bounding_boxes']['params']['boxes.length()']['state']))



	header = Header(stamp=rospy.Time.now())
	pub_msg = all_state(header, node_msg)
	pub.publish(pub_msg)



def sensor_msgs_Imu_callback(msg):
	global hz_checker
	hz_checker.callback_hz(msg, '/imu/data')
	msg_dict['/imu/data']['params']['header.seq']['value'] = msg.header.seq
	msg_dict['/imu/data']['params']['header.seq']['state'] = func_checking_value(msg.header.seq, 
						0.00, 999999.00)
def jsk_recognition_msgs_BoundingBoxArray_callback(msg):
	global hz_checker
	hz_checker.callback_hz(msg, '/velodyne/bounding_boxes')
	msg_dict['/velodyne/bounding_boxes']['params']['boxes.length()']['value'] = msg.boxes.length()
	msg_dict['/velodyne/bounding_boxes']['params']['boxes.length()']['state'] = func_checking_value(msg.boxes.length(), 
						0.00, 999999.00)





def main():
	rospy.init_node('sensor_status_node', anonymous=False)
	curr = rospy.get_rostime().to_sec()


	msg_dict['/imu/data'] = dict.fromkeys(topic_keys)
	msg_dict['/imu/data']['hz'] = 0
	msg_dict['/imu/data']['hz_state'] = 0
	msg_dict['/imu/data']['params'] = dict()

	msg_dict['/imu/data']['params']['header.seq'] = dict.fromkeys(param_keys)

	msg_dict['/velodyne/bounding_boxes'] = dict.fromkeys(topic_keys)
	msg_dict['/velodyne/bounding_boxes']['hz'] = 0
	msg_dict['/velodyne/bounding_boxes']['hz_state'] = 0
	msg_dict['/velodyne/bounding_boxes']['params'] = dict()

	msg_dict['/velodyne/bounding_boxes']['params']['boxes.length()'] = dict.fromkeys(param_keys)





	hz_checker.set_msg_t0(curr, topic = '/imu/data')
	hz_checker.set_msg_t0(curr, topic = '/velodyne/bounding_boxes')



	rospy.Subscriber('/imu/data', Imu, sensor_msgs_Imu_callback)
	rospy.Subscriber('/velodyne/bounding_boxes', BoundingBoxArray, jsk_recognition_msgs_BoundingBoxArray_callback)


	rospy.Timer(rospy.Duration(1), timer_callback)

	rospy.spin()

if __name__ == '__main__':
	main()
