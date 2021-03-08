#include "qt_talker_class.hpp"

#define NAME_SPACE "qt_talker"

int main(int argc, char** argv){
  rclcpp::init(argc, argv);

  QApplication app(argc,argv);
  QWidget* window = new QWidget;

  auto node = std::make_shared<MainDialog>(window,NAME_SPACE);
  node->show();
  
  rclcpp::Rate loop_rate(20);
  while (rclcpp::ok()){
    app.processEvents();
    loop_rate.sleep();
    node->view_rostime();
  }
}
