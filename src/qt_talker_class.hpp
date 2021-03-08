#ifndef qt_talke_class_hPP
#define qt_talke_class_hPP

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>
#include <std_msgs/msg/string.hpp>

#include <QtWidgets/QDialog>
#include <QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtCore/QString>
#include <QtWidgets/QVBoxLayout>

#include <string>
#include <time.h>
#include <thread>

#define ONE_GIGA 1000000000

class time_ros2
{
  private:
    rclcpp::Clock system_clock;
  public:
    time_ros2(){
      rclcpp::Clock system_clock(RCL_ROS_TIME);
    }

    uint64_t time_now_raw(){
  	  return system_clock.now().nanoseconds();
    }
    int32_t time_now_s(){
  	  return system_clock.now().seconds();
    }
    uint32_t time_now_ns(){
  	  uint64_t time_now = system_clock.now().nanoseconds();
	    uint64_t time_now_s = system_clock.now().seconds();
	    return uint32_t( (time_now - time_now_s*ONE_GIGA));
    }
    uint32_t time_now_ms(){
    	return uint32_t(time_now_ns()*10/ONE_GIGA);
    }
};

class MainDialog : public QDialog, public rclcpp::Node, public time_ros2
{
  Q_OBJECT
public:
  MainDialog(QWidget* parent, const std::string & name_space);
	~MainDialog();
 void view_rostime();
 uint32_t pub_time_s;

private Q_SLOTS:
  void start_record();
  void stop_record();
  
private:
  QPushButton* startButton;
  QVBoxLayout* layout;
  QGridLayout* g_layout;

  QLabel*      start_time_label;
  QLineEdit*   start_time;

  QLabel*      ros_time_label;
  QLineEdit*   ros_time;
  
  char*     save_folder_path;
  bool update_flag;
  std::string std_path;

  std_msgs::msg::Int32 time_msg;
	std::string     start_str;

  // Depend on ROS2---------------------------
	std::shared_ptr<rclcpp::Node> pub_node;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr time_pub;

};

#endif