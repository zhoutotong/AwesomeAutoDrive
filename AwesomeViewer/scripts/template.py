#!/usr/bin/env python

import sys
sys.path.append('/home/tong/Documents/AwesomeAutoDrive/AwesomeViewer/ros_tools/devel/lib/python2.7/dist-packages')

import rospy
import time
from std_msgs.msg import Header
from rostopic import ROSTopicHz
from hmi_msgs.msg import node_state
from hmi_msgs.msg import all_state

<%import_pkg_list%>
<import_pkg_list>
from <%pkg_name%>.msg import <%topic_type%>
</import_pkg_list>

hz_checker = ROSTopicHz(10, use_wtime=True)

msg_dict = {}
topic_keys = ['hz', 'hz_state', 'params']
param_keys = ['value', 'state']

pub = rospy.Publisher('<%node_name%>', all_state, queue_size = 10)

def func_checking_value(param, min, max):
	return param <= max and param >= min

def timer_callback(event):
	global hz_checker
	global pub

	node_msg = list()

<%hz_state_check%>
<hz_state_check>
	ret = hz_checker.get_hz('<%topic%>')
	if(ret):
		if isinstance(ret, tuple) and len(ret) == 5:
			msg_dict['<%topic%>']['hz'] = ret[0]
		else:
			msg_dict['<%topic%>']['hz'] = -1
		msg_dict['<%topic%>']['hz_state'] = func_checking_value(msg_dict['<%topic%>']['hz'], <%hz_min%>, <%hz_max%>)
</hz_state_check>

<%load_param_info%>
<load_param_info>
	node_msg.append(node_state('<%topic%>', 
					msg_dict['<%topic%>']['hz'], 
					msg_dict['<%topic%>']['hz_state'], 
					'<%param%>', 
					msg_dict['<%topic%>']['params']['<%param%>']['value'], 
					msg_dict['<%topic%>']['params']['<%param%>']['state']))
</load_param_info>

	header = Header(stamp=rospy.Time.now())
	pub_msg = all_state(header, node_msg)
	pub.publish(pub_msg)


<%call_back%>
<call_back>
def <%topic_label%>_callback(msg):
	global hz_checker
	hz_checker.callback_hz(msg, '')</call_back>

<callback_check_param>
	msg_dict['<%topic%>']['params']['<%param%>']['param_value'] = msg.<%param%>
	msg_dict['<%topic%>']['params']['<%param%>']['param_state'] = func_checking_value(msg.<%param%>, 
						<%param_min%>, <%param_max%>)</callback_check_param>


def main():
	rospy.init_node('<%node_name%>', anonymous=False)
	curr = rospy.get_rostime().to_sec()

<%init_dict_topic%>
<init_dict_topic>
	msg_dict['<%topic%>'] = dict.fromkeys(topic_keys)
	msg_dict['<%topic%>']['hz'] = 0
	msg_dict['<%topic%>']['hz_state'] = 0
	msg_dict['<%topic%>']['params'] = dict()
</init_dict_topic>

<init_dict_param>
	msg_dict['<%topic%>']['params']['<%param%>'] = dict.fromkeys(param_keys)
</init_dict_param>
<%hz_check%>
<hz_check>
	hz_checker.set_msg_t0(curr, topic = '<%topic%>')</hz_check>

<%sub_topic%>
<sub_topic>
	rospy.Subscriber('<%topic%>', <%topic_type%>, <%topic_label%>_callback)</sub_topic>

	rospy.Timer(rospy.Duration(1), timer_callback)

	rospy.spin()

if __name__ == '__main__':
	main()
