#include "qt_talker_class.hpp"

MainDialog::MainDialog(QWidget* parent, const std::string & name_space): QDialog(parent), Node(name_space){

	startButton = new QPushButton("START");

	start_time_label = new QLabel();
	start_time = new QLineEdit();

	ros_time_label = new QLabel();
	ros_time = new QLineEdit();

	int window_size = 500;
	update_flag = 1;
	setFixedSize(window_size,window_size/2);	

	connect(startButton,SIGNAL(clicked()),this,SLOT(start_record()));

	startButton->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));

	layout = new QVBoxLayout;
	g_layout = new QGridLayout;
	
	g_layout->addWidget(startButton,0,0);
	g_layout->addWidget(start_time,1,0);
	g_layout->addWidget(start_time_label,1,1);
	g_layout->addWidget(ros_time,2,0);
	g_layout->addWidget(ros_time_label,2,1);
	
	layout->addLayout(g_layout);
	
	setLayout(layout);

	start_time_label->setText(QString("StartTime"));
	ros_time_label->setText(QString("ROSTime"));

	time_pub = this->create_publisher<std_msgs::msg::Int32>("start_time", 10);
}

MainDialog::~MainDialog(){
	delete startButton;
	delete layout;
	delete g_layout;
	delete start_time_label;
	delete start_time;
}

void MainDialog::view_rostime(){
	std::string time_str;
	
	if(update_flag){
		time_msg.data = time_now_s() + 5+1;
		start_str = std::to_string(time_msg.data);
	}

	time_str = std::to_string(time_now_s());
	time_str += "s";
	ros_time->setText(QString::fromStdString(time_str));

	time_pub->publish(time_msg);
}

void MainDialog::start_record(){
	std::string     start_str;

	start_str = std::to_string(time_msg.data);
	start_str += "s";
	start_time->setText(QString::fromStdString(start_str));
	std::cout << "pub:" << std::to_string(time_msg.data) << "s" << std::endl;
	update_flag = 0;

	//change GUI
	startButton->setText("STOP");
	connect(startButton,SIGNAL(clicked()),this,SLOT(stop_record()));
}
void MainDialog::stop_record(){
	std::cout << "Stop record!" << std::endl;
	//change GUI
	update_flag = 1;
	startButton->setText("START");
	connect(startButton,SIGNAL(clicked()),this,SLOT(start_record()));

}