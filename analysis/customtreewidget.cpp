#include "customtreewidget.h"

CustomTreeWidget::CustomTreeWidget(QWidget *parent):QTreeWidget(parent)
{
    this->parent_window=parent;
    setVisible(true);
    this->parent_window->setWindowTitle("help");
    this->resize(parent->width()/2,parent->height());
    connect(this,&QTreeWidget::itemClicked,this,&CustomTreeWidget::clicked);

    scoll=new QScrollArea(this->parent_window);
    scoll->setGeometry(this->parent_window->width()/2,0,this->parent_window->width()/2,this->parent_window->height());

    this->label_content=new QLabel(scoll);
    scoll->setWidget(this->label_content);
    scoll->show();

    this->label_content->setVisible(true);
    this->label_content->adjustSize();//label自动适应字体大小
    this->label_content->setAlignment(Qt::AlignTop);
    this->label_content->setWordWrap(true);//自动换行
    //QFont font ( “Microsoft YaHei”, 10, 75); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    this->label_content->setFont(QFont("Microsoft YaHei",15,40));
    this->label_content->resize(this->parent_window->width()/2-20,1000);


    this->addItem(QStringList("Foreword"),"help","Foreword","");
    this->addItem(QStringList("introduction"),"Foreword","introduction","current version 9.21");

    this->addItem(QStringList("Configuration control block diagram"),"help","Configuration control block diagram","Set up the simulation algorithm by dragging the module into the window and connecting.");
    this->addItem(QStringList("configuration"),"Configuration control block diagram","configuration","Create a new block diagram drawing window in the new window; select the module classification group to which it belongs in the toolbar or module group menu. The initial position of the module group will be displayed on the left side of the workspace; left click in the toolbar of the module group. Select the module (the module is red to indicate it is selected); left click in the block diagram drawing window. Display the selected module next to the mouse click position; repeat the above steps until all required modules are placed in the desired position in the block diagram (also by dragging the module to the desired position); hold down the left mouse button and drag Complete the signal connection between the modules");
    this->addItem(QStringList("modify"),"Configuration control block diagram","modify","Press and hold the left mouse button in the center of the module or left click on the blank part of the block diagram to drag and draw the box, and release (select multiple modules) to select the module (the selected module is red) and drag to modify the block diagram. Medium module position");
    this->addItem(QStringList("copy/cut"),"Configuration control block diagram","copy/cut","Select the module by clicking the left mouse button in the center of the module (select a module) or by left-clicking on the blank part of the block diagram and dragging the drawing box, and releasing (selecting multiple modules). ); copy the selected module to the clipboard via 'Copy/Cut' or the shortcut 'ctrl+c/ctrl+x' in the 'Edit' menu bar; move the mouse position to the desired position in the block diagram window. Paste the module in the clipboard into the desired position via 'Paste' in the 'Edit' menu bar or the shortcut 'ctrl+v'");
    this->addItem(QStringList("delete"),"Configuration control block diagram","delete","Select the module by clicking the left mouse button in the center of the module (select a module) or by left-clicking on the blank part of the block diagram and dragging the drawing box, and releasing (selecting multiple modules). ); delete the selected module via 'Delete' in the 'Edit' menu bar or the shortcut 'DEL'");

    this->addItem(QStringList("moudle"),"help","moudle","Basic module group for implementing simulation algorithms");
    this->addItem(QStringList("Parameter modification"),"moudle","Parameter modification","By double clicking inside the module. Open the parameter modification dialog box, and after modifying the parameters of the current module, save the module module parameter settings with the 'OK' button.");
    this->addItem(QStringList("module size"),"moudle","module size","The left mouse button is pressed in the lower right corner of the module, and the size of the module can be freely changed by dragging.");
    this->addItem(QStringList("module label"),"moudle","module label","Each module has a default label when it is used. You can modify the custom label through the label in the module parameter dialog box.");
    this->addItem(QStringList("input/output"),"moudle","input/output","Only one signal line can be connected to the input of the module, and there is no limit on the output wiring.");

    this->addItem(QStringList("module classify"),"help","module classify","");

    this->addItem(QStringList("singal generator"),"module classify","singal generator","");
    this->addItem(QStringList("Slope"),"singal generator","Slope","A ramp signal of arbitrary slope can be sent from the start of the simulation");
    this->addItem(QStringList("Step"),"singal generator","Step","A step signal of any height can be sent from the start of the simulation");
    this->addItem(QStringList("sin"),"singal generator","sin","Send a continuous sine wave with a certain amplitude, frequency, and initial phase");
    this->addItem(QStringList("Square wave"),"singal generator","Square wave","Send a continuous square wave signal from the starting moment with a certain period and amplitude");
    this->addItem(QStringList("Sawtooth wave"),"singal generator","Sawtooth wave","Send a continuous sawtooth signal from the starting moment with a certain period, peak and trough");
    this->addItem(QStringList("Polyline"),"singal generator","Polyline","Generate a custom time series, one-to-one correspondence between the breakpoint time series and the breakpoint output sequence");
    this->addItem(QStringList("random"),"singal generator","random","Generate a continuous random signal between the 'lower signal' and 'upper limit'");

    this->addItem(QStringList("control object"),"module classify","control object","");
    this->addItem(QStringList("Constant"),"control object","Constant","Multiply the input signal by a constant and then output");
    this->addItem(QStringList("delay"),"control object","delay","Delay the input signal after a specified time");
    this->addItem(QStringList("integral"),"control object","integral","Integrate the input signal, multiply by the factor k, and output");
    this->addItem(QStringList("differential"),"control object","differential","The input signal is differentiated and then output");
    this->addItem(QStringList("First order inertia"),"control object","First order inertia","Fourth-order Runge-Kutta algorithm, improved Euler algorithm");

    this->addItem(QStringList("function"),"module classify","function","");
    this->addItem(QStringList("reciprocal"),"function","reciprocal","Regress the input value and then output");
    this->addItem(QStringList("Trigonometric function"),"function","Trigonometric function","You can choose to sine, cosine or tangent the input value and then output");
    this->addItem(QStringList("Inverse trigonometric function"),"function","Inverse trigonometric function","You can choose to find the inverse sine, arccosine or arctangent of the input value, and then output");
    this->addItem(QStringList("Absolute value function"),"function","Absolute value function","Find the absolute value of the input value, then output");
    this->addItem(QStringList("Symbolic function"),"function","Symbolic function","If the input value is greater than 0, output 1; if the output value is less than 0, output 0");
    this->addItem(QStringList("Natural logarithm function"),"function","Natural logarithm function","Find the natural logarithm of the input value and then output (the input value is greater than 0).");
    this->addItem(QStringList("Common logarithmic function"),"function","Common logarithmic function","Find the base 10 logarithm of the input value. Then output (input value is greater than 0)");
    this->addItem(QStringList("Exponential function"),"function","Exponential function","An e-based exponential function is calculated for the input value and then output");
    this->addItem(QStringList("Power function"),"function","Power function","Find a power function on the input value, then output");
    this->addItem(QStringList("sqrt"),"function","sqrt","Calculate the square root of the input value and then output (input value greater than 0)");

    this->addItem(QStringList("Comprehensive"),"module classify","Comprehensive","");
    this->addItem(QStringList("add"),"Comprehensive","add","The number of input terminals can be freely selected, and all input values of the module are summed and summed, and then output");
    this->addItem(QStringList("mul"),"Comprehensive","mul","You can choose to multiply or divide two input values");
    this->addItem(QStringList("Proportional-bias"),"Comprehensive","Proportional-bias","Multiply the input value by the proportionality factor k, plus the offset b, then output");
    this->addItem(QStringList("relationship"),"Comprehensive","relationship","Size judgment or logic judgment on two input values. When the condition is true, output 1; when the condition is false, output 0 (select comparison condition)");
    this->addItem(QStringList("logic operation"),"Comprehensive","logic operation","Perform an AND operation on two input values; or negate an input value.Extreme value; the number of input terminals can be freely selected, and the maximum or minimum value of all input values of the module is obtained and then output.");
    this->addItem(QStringList("extremum"),"Comprehensive","extremum","The number of input terminals can be freely selected, and the maximum or minimum value of all input values of the module can be obtained and then output");
    this->addItem(QStringList("Switch1"),"Comprehensive","Switch1","Single input multiple output, the last channel input value of the module indicates from which output channel the input signal is output");
    this->addItem(QStringList("Switch2"),"Comprehensive","Switch2","Multiple input single output, the last channel input value of the module indicates which channel input can reach the output channel");
    this->addItem(QStringList("curve"),"Comprehensive","curve","You can open a window to display a real-time or non-real-time curve of an exit point while the simulation is running. The x-axis direction is the time axis, and the time is changed in real time with the simulation running; the y-axis direction is the signal output display axis, which can automatically adapt to the maximum signal in the display range and change the y-axis range.");

    this->addItem(QStringList("interface"),"module classify","interface","");
    this->addItem(QStringList("input"),"interface","input","Used to bind the channel number of the signal output in the process parameter real-time acquisition device/real-time control device, and access other module input terminals in the configuration control block diagram to realize the semi-physical simulation function.");
    this->addItem(QStringList("output"),"interface","output","Used to bind the channel number of the signal input in the process parameter real-time acquisition device/real-time control device, and access other module output terminals in the configuration control block diagram to realize the semi-physical simulation function.");

    this->addItem(QStringList("single line"),"help","single line","Signal lines indicate the connection relationship between modules. All signal line branches drawn from one signal line are called signal line groups, and only one input terminal of the signal line group (ie, the signal line group can only be connected to the output end of one module to prevent multiple signal collisions)");

    this->addItem(QStringList("connect way"),"single line","connect way","");
    this->addItem(QStringList("way1"),"connect way","way1","From the output of the module: the output terminal of the left mouse button module, drag and drop the signal line");
    this->addItem(QStringList("way2"),"connect way","way2","Pull out from the signal line: the left mouse button signal line part, drag and pull out the signal line");
    this->addItem(QStringList("way3"),"connect way","way3","Automatic connection of signal line: Drag the module, align the output terminal or input terminal of the module with the terminal part of the signal line, and the signal line will be automatically connected to the output or input of the module (if the signal conflict problem mentioned above occurs, the signal Line will not be automatically connected)");
    this->addItem(QStringList("way4"),"connect way","way4","Signal integrity detection: All input terminals of the module must be connected to the signal line and the input of the signal line group must be connected to a module; all outputs of the module must be connected to the signal line and the input of the signal line group must be connected to at least one Module");

    this->addItem(QStringList("simulation"),"help","simulation","After the control system block diagram is configured, you can use the simulation function to observe various characteristics of the system. The simulation runs have two modes: 'real-time simulation' and 'non-real-time simulation'. The 'real-time simulation' real-time simulation runs through the whole process, and the 'non-real-time simulation' focuses on the simulation results. 'Real-time simulation' is only available for simulation steps >=0.1 seconds");

    this->addItem(QStringList("run"),"simulation","run","The simulation window is opened via 'Real-time simulation' and 'Non-real-time simulation' in the 'Run' menu bar. Before the simulation, the system will detect the signal integrity in the control system block diagram. If the detected signal cannot form a path, the simulation will not run (the 'open' terminal in the module is red)");
    this->addItem(QStringList("Simulation window"),"simulation","Simulation window","The coordinate system is automatically adapted to the size of the simulation window. The simulation window supports multiple curves to display together, and clicks on the curve legend in the upper right corner of the simulation window to switch whether or not to display. At the end of the simulation run or end, you can use the 'z' key to stop the real-time drawing of the curve. By dragging the position of the curve in the curve display box, you can observe the position of the drawn curve at any time (at this time, just stop the curve drawing, simulation) Still running, you can redraw the curve to the simulation run time by pressing the 'z' key again)");
    this->addItem(QStringList("result saving"),"simulation","result saving","After the simulation run ends, the system will prompt whether to save the current simulation results:'Yes', the system will store the simulation step, simulation time and simulation results in a file (or database). If the simulation window is forcibly closed before the simulation ends, the simulation data will not be saved. You can choose to save the simulation data by suspending the simulation midway.");

    this->addItem(QStringList("Curve analysis"),"help","Curve analysis","After each simulation run, the results of the run can be saved. The curve analysis function can display the saved multiple different simulation results in a single curve window for analysis (you can view the simulation data at any time in the selected time period). You can choose to display from any time period from the start and end time of the simulation run to the end time");

    this->addItem(QStringList("step1"),"Curve analysis","step1","You can open the settings dialog by selecting the Curve Analysis command from the Run menu bar");
    this->addItem(QStringList("step2"),"Curve analysis","step2","In the dialog box, select Join Module and select the module file to be added from the open folder.");
    this->addItem(QStringList("step3"),"Curve analysis","step3","Select the time range to display");

    this->addItem(QStringList("Document management"),"help","Document management","Management configuration block diagram file");

    this->addItem(QStringList("new"),"Document management","new","New configuration window");
    this->addItem(QStringList("open"),"Document management","open","open the configuration block file");
    this->addItem(QStringList("save"),"Document management","save","save the configuration block file");
    this->addItem(QStringList("save as"),"Document management","save as","save the configuration block file as the other file");
    this->addItem(QStringList("export"),"Document management","export","Export the algorithm set up by the current configuration block diagram, and export the format file to a .c file. After compiling into the executable file of the target platform, generate a dynamic link library of the program, and bind the actual channel number and simulation algorithm through the program call. Real-time control of objects in virtual channel numbers");

    this->addItem(QStringList("Diagnostic fault"),"help","Diagnostic fault","Detect different types of faults that occur during system control");
    this->addItem(QStringList("Fault preset"),"Diagnostic fault","Fault preset","Open the fault preset window, select the fault type (jump during signal transmission, etc.), fault generation time, fault duration and fault action object, send an instruction to the fault generator, and the fault generator receives the fault according to the given command. Signal of the specified channel for fault generation");
    this->addItem(QStringList("fault Diagnostic"),"Diagnostic fault","fault Diagnostic","Open the fault diagnosis window, the window will display the running status of the channels in all cabinets. When the system detects the channel signal fault, it will display different colors under the corresponding channel to indicate different fault types");

    this->addItem(QStringList("Effectiveness assessment"),"help","Effectiveness assessment","Evaluate the simulation algorithm based on simulation data stored in the database after simulation");

    this->addItem(QStringList("未完待续"),"help","end","未完待续");


}
void CustomTreeWidget::resizeEvent(QResizeEvent *)
{
}
int CustomTreeWidget::addItem(QStringList item, QString parentKey, QString theKey,QString content)
{
    QTreeWidgetItem* temp_item;
        /// 生成到父级节点下
    QMap<QString,QTreeWidgetItem*>::iterator iter_item = itemMap_.find(parentKey);
    if (iter_item == itemMap_.end())
    {
        temp_item = new QTreeWidgetItem(this,item);
    }
    else
    {
        temp_item = new QTreeWidgetItem(iter_item.value(), item);
    }/// 判断
    if (!theKey.isEmpty())
    {
        itemMap_.insert(theKey,temp_item);
        itemstring_.insert(theKey,content);
    }
    return 0;
}
void CustomTreeWidget::clicked()
{
    QString str=*this->itemstring_.find(this->itemMap_.key(this->currentItem()));
    this->label_content->setText(str);
}
