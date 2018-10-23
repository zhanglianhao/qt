#include "analysis.h"
#include "mainwindow.h"
analysis::analysis(QWidget *parent) : QMainWindow(parent),ui(new UI)
{
    init();
   // MainWindow* windouw=new MainWindow(this);
        //窗体1，其父窗体为滚动区域
    //设置滚动区域的窗体
   //     windouw->setGeometry(0, 0, 400, 400);
   //     windouw->show();
}
void analysis::init()
{
    analysis::menu();
    group();
    tool();
    init_button();
    setWindowTitle("仿真软件");
    if(autosave==1)//开启自动保存
    {
        auto_save();
    }
    this->setFocusPolicy(Qt::StrongFocus);
}
void analysis::auto_save()
{
    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    mDataTimer.start(1000*60*5);//每隔5min自动保存
    this->saveall();
}
void analysis::timerSlot()
{
    this->saveall();
    mDataTimer.start(1000*60*5);//每隔5min自动保存
    save_state();
    //this->ui->statusBar->addWidget()
}
void analysis::save_state()
{
    this->ui->statusBar->showMessage("save",1000);
}
void analysis::statr_message(QString message,int time)
{
    this->ui->statusBar->showMessage(message,time);
}
QTreeWidget2::QTreeWidget2(QWidget *parent):QTreeWidget(parent)
{

}
void QTreeWidget2::init(analysis* parent)
{
    this->parent=parent;
    connect(this, &QTreeWidget::itemDoubleClicked, this, &QTreeWidget2::double_click);

}
void QTreeWidget2::double_click()
{}
void QTreeWidget2::mouseReleaseEvent(QMouseEvent *event)
{
    this->parent->project_event();
    if(event->button()==Qt::RightButton)
    {
        QString project;
        project=this->parent->str_to_map.key(this->currentItem());
        this->parent->update_tree(project);
    }
    else if(event->button()==Qt::LeftButton)
    {
    }
}
void analysis::menu()
{
    ui->setupUi(this);
    QAction* analysis;

    //工程区域
    project=new QTreeWidget2(this->ui->centralWidget);
    project->init(this);
    project->setGeometry(0,0,140,1080);

    custom_menu->fileMenu = menuBar()->addMenu(tr("&文件"));
    analysis = new QAction(tr("&新建工程"), this);
    custom_menu->fileMenu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::newproject);

    analysis = new QAction(tr("&打开工程"), this);
    custom_menu->fileMenu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::openproject);

    analysis = new QAction(tr("&新建文件"), this);
    custom_menu->fileMenu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::newwindow);

    analysis = new QAction(tr("&打开文件"), this);
    custom_menu->fileMenu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::open);
    //connect(analysis, &QAction::triggered, this, &MainWindow::analysis);

    analysis = new QAction(tr("&保存"), this);
    custom_menu->fileMenu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::save);

    analysis = new QAction(tr("&另存"), this);
    custom_menu->fileMenu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::save_as);

    analysis = new QAction(tr("&算法导出"), this);
    custom_menu->fileMenu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::export_algorithm);

    /*
    analysis = new QAction(tr("&rename"), this);
    custom_menu->fileMenu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::rename);

    analysis = new QAction(tr("&add new"), this);
    custom_menu->fileMenu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::addnewfile);

    analysis = new QAction(tr("&add exist"), this);
    custom_menu->fileMenu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::addexistfile);
    */
    custom_menu->edit=menuBar()->addMenu(tr("&编辑"));
    analysis = new QAction(tr("&复制  Crtl+C"), this);
    custom_menu->edit->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::clonemoudle);

    analysis = new QAction(tr("&剪切  Crtl+X"), this);
    custom_menu->edit->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::cutmoudle);

    analysis = new QAction(tr("&粘贴  Crtl+V"), this);
    custom_menu->edit->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::pastemoudle);

    analysis = new QAction(tr("&删除  Delete"), this);
    custom_menu->edit->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::deleteany);   

    custom_menu->moudlegroup=menuBar()->addMenu(tr("&模块"));
    custom_menu->action_group.push_back(new QAction(tr("&信号"), this));
    custom_menu->action_group.push_back(new QAction(tr("&对象"), this));
    custom_menu->action_group.push_back(new QAction(tr("&函数"), this));
    custom_menu->action_group.push_back(new QAction(tr("&综合"), this));
    custom_menu->action_group.push_back(new QAction(tr("&接口"), this));
    for(int i=0;i<custom_menu->action_group.size();i++)
    {
        custom_menu->moudlegroup->addAction(custom_menu->action_group[i]);
        connect(custom_menu->action_group[i], &QAction::triggered, this, &analysis::findgroup_menu);
    }

    custom_menu->run=menuBar()->addMenu(tr("&运行"));
    analysis = new QAction(tr("&real"), this);
    custom_menu->run->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::test);

    analysis = new QAction(tr("&un-real"), this);
    custom_menu->run->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::test_simulation);



    analysis = new QAction(tr("&数据分析"), this);
    custom_menu->run->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::data_analysis);

    analysis = new QAction(tr("&效能评估"), this);
    custom_menu->run->addAction(analysis);

    analysis = new QAction(tr("&故障生成"), this);
    custom_menu->run->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::fault_window);

    analysis = new QAction(tr("&算法导出"), this);
    custom_menu->run->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::test_algorithm);

    custom_menu->window=menuBar()->addMenu(tr("&窗口"));
    analysis = new QAction(tr("&新建"), this);
    custom_menu->window->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::newwindow);

    custom_menu->helpMenu=menuBar()->addMenu(tr("&帮助"));
    analysis = new QAction(tr("&帮助"), this);
    custom_menu->helpMenu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::help);

    custom_menu->closeMenu=menuBar()->addMenu(tr("&关闭"));
    analysis=new QAction(tr("&关闭"),this);
    custom_menu->closeMenu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &QWidget::close);

    pop_menu();
    //connect(project, &QTreeWidget::itemClicked, this, &analysis::project_event);
}
void analysis::pop_menu()
{
    //弹出式菜单设计
    QAction* analysis;
    custom_menu->pop_up_menu=new QMenu(project);
    analysis = new QAction(tr("&new file"), this);
    custom_menu->pop_up_menu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::newwindow);

    analysis = new QAction(tr("&open file"), this);
    custom_menu->pop_up_menu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::open);

    analysis = new QAction(tr("&new project"), this);
    custom_menu->pop_up_menu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::newproject);

    analysis = new QAction(tr("&open project"), this);
    custom_menu->pop_up_menu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::openproject);

    analysis = new QAction(tr("&add new file"), this);
    custom_menu->pop_up_menu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::addnewfile);

    analysis = new QAction(tr("&add exist file"), this);
    custom_menu->pop_up_menu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::addexistfile);

    analysis = new QAction(tr("&remove file"), this);
    custom_menu->pop_up_menu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::remove_file);

    analysis = new QAction(tr("&remove project"), this);
    custom_menu->pop_up_menu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::remove_project);

    analysis = new QAction(tr("&rename"), this);
    custom_menu->pop_up_menu->addAction(analysis);
    connect(analysis, &QAction::triggered, this, &analysis::rename);
    custom_menu->pop_up_menu->setVisible(false);
}
void analysis::group()
{
    //若有扩展新的buttongroup需在此添加buttonGroup
    custom_menu->buttom_group.append(ui->buttonGroup1);
    custom_menu->buttom_group.append(ui->buttonGroup2);
    custom_menu->buttom_group.append(ui->buttonGroup3);
    custom_menu->buttom_group.append(ui->buttonGroup4);
    custom_menu->buttom_group.append(ui->buttonGroup5);
    for(int i=0;i<custom_menu->buttom_group.size();i++)
    {

        foreach (QAbstractButton* button,custom_menu->buttom_group[i]->buttons())
        {
            button->setVisible(false);
        }

    }
}
void analysis::fault_window()
{
    //qDebug()<<1;
    fault_dialog* fault=new fault_dialog();
    fault->show();
    //if(fault->exec())
    //{

    //}
}
void analysis::newproject()
{
    save_as(2);
}
void analysis::openproject()
{
    openway=1;
    open();
}
void analysis::project_event()
{
    //this->custom_menu->pop_up_menu->move(cursor().pos());
    //this->custom_menu->pop_up_menu->show();

    QString url=this->str_to_map.key(project->currentItem());
    QStringList str=this->url_to_name(url);
    if(str[1]=="pro")
    {
        this->current_project_id=this->project_url.indexOf(url);
        for(int i=0;i<this->url_group[current_project_id].size();i++)
            project_files_ope(this->url_group[current_project_id][i]);
    }
    else if(str[1]=="ifg")
    {
        QString parent_name=this->str_to_map.key(project->currentItem()->parent());
        this->current_project_id=this->project_url.indexOf(parent_name);
        project_files_ope(url);
        //qDebug()<<this->current_project_id<<current_file_id;
    }
}
void analysis::project_files_ope(QString url)
{
    this->current_file_id=this->url_group[current_project_id].indexOf(url);
    int flag=0;
    for(int i=0;i<this->mainwindow_group.size();i++)
    {
        if(this->mainwindow_group[i]->url==url)
        {
            this->mainwindow_current=this->mainwindow_group[i];
            flag=1;
            break;
        }
    }
    if(flag==0)//file未打开或已关闭
        openfile(url,1,1);
}
void analysis::addnewfile()
{
    newwindow();
    this->mainwindow_current->project_url=this->project_url[this->current_project_id];
    this->open_way=true;
    this->save_as(0);
    this->open_way=false;
    //qDebug()<<this->mainwindow_current->url;
    if(this->mainwindow_current->url=="")
    {
        int index=this->mainwindow_group.indexOf(mainwindow_current);
        emit this->scoll_group[index]->close();
    }
    else
        this->addfile(this->mainwindow_current->url);
}
void analysis::addexistfile()
{
    QStringList fileNamelist=QFileDialog::getOpenFileNames(this,tr("add exist file"),"",tr("Config Files (*.ifg)"));
    for(int m=0;m<fileNamelist.size();m++)
    {
        QString fileName=fileNamelist[m];
        QStringList lis=url_to_name(fileName);
        if(lis[2]==url_to_name(this->project_url[this->current_project_id])[2])//添加文件位于工程所在目录，不需要复制文件
        {
            if(this->url_group[this->current_project_id].indexOf(fileName)!=-1)
            {
                this->statr_message("file already exist current project",1000);
            }
            else
            {
                this->openfile(fileName,1,0);
                this->addfile(fileName);
            }
            //if(this->openfile(fileName,1,0)==true)
        }
        else
        {
            int i=0;
            //检查欲添加的文件是否与工程目录中存在的文件重名
            for(i=0;i<this->url_group[this->current_project_id].size();i++)
                if(url_to_name(this->url_group[this->current_project_id][i])[0]==lis[0])
                    break;
            if(i!=this->url_group[this->current_project_id].size())
            {
                this->statr_message("current project path has the same name",1000);
            }
            else
            {
                QString newfilename=url_to_name(this->project_url[this->current_project_id])[2]+lis[0]+".ifg";
                //bool open_flag=this->openfile(newfilename,1,0);
                if(fileName!=newfilename)//所添加的文件是否为该工程所在目录下的文件
                {
                    QFile* file=new QFile(newfilename);
                    if(file->exists()==true)
                       file->remove();
                    QFile::copy(fileName,newfilename);
                    //if(this->openfile(newfilename,1,0)==true)
                    //    this->addfile(newfilename);
                }
                this->openfile(newfilename,1,0);
                this->addfile(newfilename);
            }
        }
    }
}
void analysis::newwindow()
{
   scoll *s = new scoll(nullptr,this);
   s->setWindowTitle("window"+QString::number(windowid));
   s->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   this->mainwindow_current=new MainWindow(s);
   this->mainwindow_current->name="";//"window"+QString::number(windowid);
   this->mainwindow_current->url="";//QDir::currentPath()+this->mainwindow_current->name;
   this->mainwindow_current->id=this->windowid++;
   this->mainwindow_current->parent=this;
   this->mainwindow_group.push_back(this->mainwindow_current);
   this->scoll_group.push_back(s);
   s->setWidget(this->mainwindow_current);
   this->mainwindow_current->setGeometry(0, 0, 2000, 2000);
   //mid->resize(500,500);
   //s->setGeometry(100,100,800,600);
   QMdiSubWindow* mid=ui->area->addSubWindow(s);
   mid_group.push_back(mid);
   s->show();
   //s->show();
}
void analysis::data_analysis()
{
    data_dialog* data=new data_dialog();
    if(data->exec())
    {
        for(int i=0;i<data->checkbox_group_right.size();i++)
        {
            int index=data->button_group.indexOf(data->checkbox_group_right[i]);
            qDebug()<<data->url[index];
        }
    }
}
void analysis::rename()
{
    if(this->project_url.indexOf((this->str_to_map.key(this->project->currentItem())))!=-1)//修改工程名字
    {
        bool ok;
        QString newname=QInputDialog::getText(this,"rename","",QLineEdit::Normal,url_to_name(project_url[current_project_id])[0],&ok);
        if(ok)
        {
            if(url_to_name(project_url[current_project_id])[0]==newname)
                return;
            QString forma_pre=this->url_to_name(project_url[current_project_id])[2];
            QString forma=this->url_to_name(project_url[current_project_id])[1];
            QString newurl=forma_pre+newname+"."+forma;
            QTreeWidgetItem* item=*this->str_to_map.find(project_url[current_project_id]);
            QString oldkey=this->str_to_map.key(item);
            this->str_to_map.remove(oldkey);
            this->str_to_map.insert(newurl,item);
            item->setText(0,newname);
            QFile* file=new QFile(project_url[current_project_id]);
            file->rename(newurl);

            project_url[current_project_id]=newurl;

            for(int i=0;i<this->url_group[current_project_id].size();i++)
            {
                int index=this->find_with_url(this->url_group[current_project_id][i]);
                if(index!=-1)
                {
                    this->mainwindow_group[index]->project_url=newurl;//将修改过的工程名称在各子文件下进行保存
                    this->mainwindow_group[index]->save_as(new QFile(this->mainwindow_group[index]->url),1);
                }
            }
        }

        return;
    }


    if(this->mainwindow_current==nullptr)
    {
        this->statr_message("no file is selected",1000);
        return;
    }
    QString oldname=this->mainwindow_current->name;
    QString oldurl=this->mainwindow_current->url;
    QString forma_pre=this->url_to_name(oldurl)[2];
    QString forma=this->url_to_name(oldurl)[1];
    QString newurl;
    bool ok;
    int flag=0;
    QString newname=QInputDialog::getText(this,"rename","",QLineEdit::Normal,oldname,&ok);
    if(ok)
    {
        if(newname==oldname)
            return;
        newurl=forma_pre+newname+"."+forma;
        int i=0;
        //检查是否在工程中
        for(i=0;i<this->url_group.size();i++)
            if(this->url_group[i].indexOf(oldurl)!=-1)
                break;
        if(i==this->url_group.size())//不在工程中，直接改名即可
        {
        }
        else
        {
            if(this->url_group[i].indexOf(newurl)!=-1)//与当前工程下的文件重名
            {
                flag=1;
                QStringList lis;
                lis.push_back("yes");
                lis.push_back("cancel");
                if(custom_message_box("whether cover the file",lis)==2)
                    return;
            }
            this->modify_name(oldurl,newurl,1);
        }
        int index=this->find_with_url(oldurl);
        this->mainwindow_current=this->mainwindow_group[index];
        //int index=this->mainwindow_group.indexOf(this->mainwindow_current);
        this->scoll_group[index]->setWindowTitle(newname);
        QFile* file=new QFile(oldurl);
        if(flag==1)
        {
            file->remove();
        }
        else
            file->rename(newurl);
        this->mainwindow_current->name=newname;
        this->mainwindow_current->url=newurl;
        this->mainwindow_current->save_as(new QFile(newurl),1);
    }
}
void analysis::open()
{
    QStringList fileNameList;
    QString fileName;
    /*QFileDialog* fd = new QFileDialog(this);//创建对话框
    fd->resize(240,320);    //设置显示的大小
    fd->setViewMode(QFileDialog::List);  //设置浏览模式，有 列表（list） 模式和 详细信息（detail）两种方式
    if(fd->exec()==QDialog::Accepted)   //如果成功的执行
    {
    fileNameList=fd->selectedFiles();      //返回文件列表的名称
    fileName = fileNameList[0];            //取第一个文件名
    QFile* file=new QFile(fileName);
    this->newwindow();
    this->mainwindow_current->open(file);
    }
    else
    fd->close();
    */
    if(openway==0)
        fileName=QFileDialog::getOpenFileName(this,tr("打开文件"),"",tr("Config Files (*.ifg)"));
    else if(openway==1)
        fileName=QFileDialog::getOpenFileName(this,tr("打开工程"),"",tr("Config Files (*.pro)"));
    if(!fileName.isNull())
    {
        this->openfile(fileName,0,0);
    }
    openway=0;
}
bool analysis::openfile(QString fileName,int way,int openway)
{
    QString name="";
    QString forma="";//文件后缀名
    QStringList str=this->url_to_name(fileName);
    name=str[0];
    forma=str[1];
    if(forma=="ifg")//打开文件
    {
        if(way==0)
        {
            for(int i=0;i<this->url_group.size();i++)//判断是否文件已经存在于现有工程中
            if(this->url_group[i].indexOf(fileName)!=-1)
            {
                this->statr_message("file already exists",1000);
                return false;
            }
            QString url_temp=exist_project(fileName);
            if(url_temp!="false")
            {
                this->statr_message("file already exists in "+this->url_to_name(url_temp)[0]+" projects",1000);
                return false;
            };//判断文件是否存在于未打开的工程中
        }
        for(int i=0;i<this->mainwindow_group.size();i++)//判断文件是否未存在于现有工程但是已经打开
            if(this->mainwindow_group[i]->url==fileName)
            {
                this->statr_message("file already exists",1000);
                return false;
            }
        QFile* file=new QFile(fileName);
        if(file->exists()==false)//文件不存在
            return false;
        this->newwindow();
        this->mainwindow_current->open(file);
        this->mainwindow_current->save_open=true;
        this->mainwindow_current->modify=false;
        this->windowid--;
        this->mainwindow_current->name=name;
        this->mainwindow_current->url=fileName;
        //if(openway==1)//通过工程打开文件
        //    this->mainwindow_current->project_url=this->project_url[this->current_project_id];//该文件已存在于工程中，不需要再次加入工程
        int index=this->mainwindow_group.indexOf(this->mainwindow_current);
        this->scoll_group[index]->setWindowTitle(name);
    }
    else if(forma=="pro")//打开工程
    {
        if(this->project_url.indexOf(fileName)!=-1)
        {
            this->statr_message("project had exist",1000);
            return false;
        }
        QStringList str;
        this->project_url.push_back(fileName);
        this->url_group.push_back(str);
        QTreeWidgetItem* item=new QTreeWidgetItem(project,QStringList(this->url_to_name(project_url[project_url.size()-1])[0]));
        this->str_to_map.insert(project_url[project_url.size()-1],item);
        this->current_project_id=this->project_url.size()-1;
        QFile* file=new QFile(this->project_url[project_url.size()-1]);
        if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"error";
            return false;
        }
        QDataStream ds(file);
        this->url_group_temp.clear();
        ds>>this->url_group_temp;
        file->close();
        //qDebug()<<url_group_temp[0];
        open_files();
    }
    return true;

}
void analysis::open_files()
{
    QString str="";
    for(int i=0;i<this->url_group_temp.size();i++)
    {
        QStringList lis=this->url_to_name(this->project_url[current_project_id]);
        str=lis[2]+this->url_to_name(this->url_group_temp[i])[0]+".ifg";
        if(openfile(str,1,1)==false)//工程下文件地址由工程的相对地址求出
        {
            this->statr_message("file is not exist or the path error ",1000);
        }
        else
            if(this->url_group[current_project_id].indexOf(str)==-1)
            {
                this->addfile(str);
            }
    }
}
void analysis::save()
{
    if(this->mainwindow_current==nullptr)
    {
        this->statr_message("no file is selected",1000);
        return;
    }
    this->mainwindow_current->save();
}
void analysis::saveall()
{
    for(int i=0;i<this->mainwindow_group.size();i++)
    {
        if(this->mainwindow_group[i]->modify==true)
        {
            this->mainwindow_current=this->mainwindow_group[i];
            this->mainwindow_group[i]->save();
        }
    }
}
QStringList analysis::url_to_name(QString fileName)//地址转文件名
{
    int index1=0,index2=0;
    QString name="";//文件名
    QString forma="";//文件格式
    QString pre_forma="";
    QStringList str;
    for(int i=fileName.size()-1;i>=0;i--)
    {
        if(fileName[i]=='.')
        {
            index1=i-1;
            break;
        }
    }
    for(int i=index1+2;i<fileName.size();i++)
        forma+=fileName[i];

    for(int i=fileName.size()-1;i>=0;i--)
    {
        if(fileName[i]=='/'||fileName[i]=='\\')
        {
            index2=i+1;
            break;
        }
    }
    for(int i=index2;i<=index1;i++)
    {
        name+=fileName[i];
    }
    for(int i=0;i<index2;i++)
        pre_forma+=fileName[i];
    str.push_back(name);
    str.push_back(forma);
    str.push_back(pre_forma);
    return str;
}
void analysis::save_as(int way)
{
    QStringList fileNameList;
    QString fileName;
    /*
    QFileDialog* fd = new QFileDialog(this);//创建对话框
    fd->resize(240,320);    //设置显示的大小
    fd->setViewMode(QFileDialog::List);  //设置浏览模式，有 列表（list） 模式和 详细信息（detail）两种方式
    if(fd->exec()==QDialog::Accepted)   //如果成功的执行
    {
    fileNameList=fd->selectedFiles();      //返回文件列表的名称
    fileName = fileNameList[0];            //取第一个文件名
    QFile* file=new QFile(fileName);
    this->mainwindow_current->save(file);
    }
    else
    fd->close();
    */
    if(way==0)
    {
        if(this->mainwindow_current==nullptr)
        {
            this->statr_message("no file is selected",1000);
            return;
        }

        if(this->open_way==false)
             fileName=QFileDialog::getSaveFileName(this,tr("save as"),this->mainwindow_current->url==""?"":url_to_name(this->mainwindow_current->url)[2],tr("Config Files (*.ifg)"));
        else
            fileName=QFileDialog::getSaveFileName(this,tr("add new file"),url_to_name(this->project_url[this->current_project_id])[2],tr("Config Files (*.ifg)"));
    }
    else if(way==1)
        fileName=QFileDialog::getSaveFileName(this,tr("save as"),"",tr("Config Files (*.txt)"));
    else if(way==2)
        fileName=QFileDialog::getSaveFileName(this,tr("新建工程"),"",tr("Config Files (*.pro)"));
    if(!fileName.isNull())
    {
        QString name="";
        name=this->url_to_name(fileName)[0];
        QFile* file=new QFile(fileName);
        if(way==0)
        {
            if(this->open_way==false&&this->mainwindow_current->project_url!="-1")//表示当前操作为另存为，且位于当前工程下，需要同时修改在工程中的名字
            {
                current_project_id=this->project_url.indexOf(this->mainwindow_current->project_url);
                if(this->url_group[current_project_id].indexOf(fileName)!=-1)//与当前工程下的文件重名
                {
                    QStringList lis;
                    lis.push_back("yes");
                    lis.push_back("cancel");
                    if(custom_message_box("whether cover the file",lis)==2)
                        return;
                }
                modify_name(this->mainwindow_current->url,fileName,0);
            }
            else//文件另存为时，若重名并且重名文件已经在软件中打开，则另存为文件会覆盖已经打开的文件，若文件从属于工程，则另存为文件也将从属于工程
            {
                MainWindow* mainwindoe_temp=this->mainwindow_current;
                int index1=this->find_with_url(fileName);
                if(index1!=-1)
                {
                    this->mainwindow_group[index1]->save_as(file,1);
                    emit this->scoll_group[index1]->close();
                }
                this->mainwindow_current=mainwindoe_temp;
                int m=0;
                for(m=0;m<this->url_group.size();m++)
                    if(url_group[m].indexOf(fileName)!=-1)
                        break;
                if(m!=this->url_group.size())
                    this->mainwindow_current->project_url=this->project_url[m];
            }
            this->mainwindow_current->name=name;
            this->mainwindow_current->url=fileName;
            //qDebug()<<fileName;
            int index=this->mainwindow_group.indexOf(this->mainwindow_current);
            this->scoll_group[index]->setWindowTitle(name);
            this->mainwindow_current->save_as(file,0);
            if(this->mainwindow_current->save_open==false)
                this->mainwindow_current->save_open=true;
            //qDebug()<<1;
        }
        else if(way==1)
        {
            if(this->run_current->url[this->run_current->current_graph_id]=="")
                this->run_current->url[this->run_current->current_graph_id]=fileName;
            this->run_current->save_data(file,this->run_current->current_graph_id);
        }
        else if(way==2)
        {
            QStringList str;
            this->project_url.push_back(fileName);
            this->url_group.push_back(str);
            QTreeWidgetItem* item=new QTreeWidgetItem(project,QStringList(this->url_to_name(project_url[project_url.size()-1])[0]));
            this->str_to_map.insert(project_url[project_url.size()-1],item);
            this->current_project_id=this->project_url.size()-1;
            create_empty_project(fileName);
        }
    }
}
int analysis::find_file_project(QString url)
{
    for(int i=0;i<this->url_group.size();i++)
        if(this->url_group[i].indexOf(url)!=-1)
            return i;
    return -1;
}
void analysis::modify_name(QString oldname,QString newname,int way)
{
    int old_index=find_file_project(oldname);
    int new_index=find_file_project(newname);
    if(old_index!=-1)//表明文件从属于现有工程
    {
        this->current_project_id=old_index;
        QTreeWidgetItem* item=*this->str_to_map.find(oldname);
        QString oldkey=this->str_to_map.key(item);
        this->str_to_map.remove(oldkey);
        if(new_index==-1)
        {
            this->str_to_map.insert(newname,item);
            item->setText(0,url_to_name(newname)[0]);

            int index1=url_group[old_index].indexOf(oldname);
            url_group[old_index][index1]=newname;
            write_project();//写入project数据
            //item->parent()->removeChild(item);
            //QTreeWidgetItem* parent=*this->str_to_map.find(project_url[new_index]);
            //parent->addChild(item);
        }
        else
        {
            item->parent()->removeChild(item);
            delete item;
            project_files_ope(newname);
            this->mainwindow_current=this->mainwindow_group[find_with_url(newname)];
            this->mainwindow_current->save_as(new QFile(this->mainwindow_current->url),1);
            emit this->scoll_group[find_with_url(newname)]->close();
            url_group[old_index].removeOne(oldname);
            write_project();//写入project数据
        }
        if(way==0)
        {
            int index=find_with_url(oldname);
            this->mainwindow_current=this->mainwindow_group[index];
            this->mainwindow_group[index]->project_url="-1";//将文件从所在工程中移除
            this->mainwindow_group[index]->save_as(new QFile(oldname),1);
            this->mainwindow_group[index]->project_url=project_url[old_index];
        }
    }
    else//文件独立于工程中
    {
        /*
        MainWindow* mainwindoe_temp=this->mainwindow_current;
        int index1=this->find_with_url(newname);
        if(index1!=-1)
        {
            this->mainwindow_group[index1]->save_as(new QFile(newname),1);
            emit this->scoll_group[index1]->close();
        }
        this->mainwindow_current=mainwindoe_temp;
        if(new_index!=-1)
        qDebug()<<project_url[new_index];
        if(new_index!=-1)
            this->mainwindow_current->project_url=project_url[new_index];
       */
    }
    /*
    int i=0; 
    for(i=0;i<this->url_group.size();i++)
        if(url_group[i].indexOf(oldname)!=-1)
            break;
    if(i!=this->url_group.size())//需要另存为的文件存在于现有工程中
    {
        this->current_project_id=i;
        if(url_group[i].indexOf(newname)!=-1)//重名 首先移除旧文件
        {
            this->removefile(newname,0);
            //QFile* file=new QFile(newname);
            //file->remove();
        }

        QTreeWidgetItem* item=*this->str_to_map.find(oldname);
        QString oldkey=this->str_to_map.key(item);
        this->str_to_map.remove(oldkey);
        this->str_to_map.insert(newname,item);
        item->setText(0,url_to_name(newname)[0]);

        if(way==0)
        {
            int index=find_with_url(oldname);
            this->mainwindow_group[index]->project_url="-1";//将文件从所在工程中移除
            this->mainwindow_group[index]->save_as(new QFile(oldname),1);
            this->mainwindow_group[index]->project_url=project_url[i];
        }

        int index1=url_group[i].indexOf(oldname);
        url_group[i][index1]=newname;
        write_project();//写入project数据
    }
    */
}
void analysis::close()
{
}
void analysis::help()
{
    this->helpwindow=new QWidget();
    this->helpwindow->show();
    this->customtree=new CustomTreeWidget(this->helpwindow);
}
void analysis::tool()
{
    //若有扩展新的buttongroup需在此添加menu按钮
    custom_menu->pushbutton.push_back(new QPushButton(tr("&信号")));
    custom_menu->pushbutton.push_back(new QPushButton(tr("&对象")));
    custom_menu->pushbutton.push_back(new QPushButton(tr("&函数")));
    custom_menu->pushbutton.push_back(new QPushButton(tr("&综合")));
    custom_menu->pushbutton.push_back(new QPushButton(tr("&接口")));

    for(int i=0;i<this->custom_menu->pushbutton.size();i++)
    {
        ui->mainToolBar->addWidget(this->custom_menu->pushbutton[i]);
        connect(this->custom_menu->pushbutton[i], &QAbstractButton::clicked, this, &analysis::findgroup);
    }
    QPushButton* button=new QPushButton(tr("实时测试"));
    ui->mainToolBar->addWidget(button);
    connect(button, &QAbstractButton::clicked, this, &analysis::test);
    button=new QPushButton(tr("non-real"));
    ui->mainToolBar->addWidget(button);
    connect(button, &QAbstractButton::clicked, this, &analysis::test_simulation);
    //connect(ui->mainToolBar, &QToolBar::orientationChanged, this, &MainWindow::toolchange);
    //qDebug(group2->hide());
}
void analysis::init_button()
{
    for(int i=0;i<this->custom_menu->buttom_group.size();i++)
    {
        QButtonGroup* group=this->custom_menu->buttom_group[i];
        foreach(QAbstractButton* but,group->buttons())
        {
            connect(but, &QAbstractButton::pressed, this, &analysis::on_pressed);
        }
    }
}
bool analysis::find(QList<int> group,int index)
{
    for(int i=0;i<group.size();i++)
        if(group[i]==index)
            return false;
    return true;
}
void analysis::clonemoudle()
{
    this->mainwindow_current->clonemoudle();
}
void analysis::cutmoudle()
{
    this->mainwindow_current->cutmoudle();
}
void analysis::pastemoudle()
{
    this->child->paste_flag=true;
}
void analysis::deleteany()
{
    this->mainwindow_current->deleteany();
}
void analysis::findgroup_menu()
{
    int index;
    QAction* action=qobject_cast<QAction*>(sender());
    index=this->custom_menu->action_group.indexOf(action);
    findgroup_way(index);
}
void analysis::findgroup()
{
    int index;
    QPushButton* button=qobject_cast<QPushButton*>(sender());
    index=this->custom_menu->pushbutton.indexOf(button);
    findgroup_way(index);
}
void analysis::findgroup_way(int index)
{
    if(find(custom_menu->button_index,index+1))
    {
        foreach(QAbstractButton* button,custom_menu->buttom_group[index]->buttons())
    {
        button->setVisible(true);


    }
        set_position(index+1,true);
       // custom_menu->pushbutton[0]->setAutoFillBackground(true);
        set_shadow(custom_menu->pushbutton[index]);
    }
    else
    {
        foreach(QAbstractButton* button,custom_menu->buttom_group[index]->buttons())
        {
            button->setVisible(false);

        }
        set_position(index+1,false);
       remove_shadow(custom_menu->pushbutton[index]);
    }
}
void analysis::set_position(int index,bool flag)
{
    int i;
    if(flag)
    {
        for(i=0;i<custom_menu->button_index.size();i++)
        if(custom_menu->button_index[i]>index)
            break;
        custom_menu->button_index.insert(i,index);
       // printf_s("yes");
    }
    else
    {
        for(i=0;i<custom_menu->button_index.size();i++)
        if(custom_menu->button_index[i]==index)
        {
            custom_menu->button_index.removeAt(i);
            break;
        }
    }
    int x=0,y;
    for(i=0;i<custom_menu->button_index.size();i++)
    {
       QButtonGroup* group=custom_menu->buttom_group[custom_menu->button_index[i]-1];
       if(i==0)
       {
           x=custom_menu->group_x_start;
           y=custom_menu->group_y_start;
       }
       else
       {
           x+=custom_menu->buttom_group[custom_menu->button_index[i-1]-1]->buttons()[0]->geometry().width();
           y=custom_menu->group_y_start;
           x+=2;
           //qDebug()<<custom_menu->button_index.size();
       }
       foreach(QAbstractButton* button,group->buttons())
       {
          // button->setGeometry(x,y,custom_menu->group_y_interval,custom_menu->group_y_interval);
           setbutton_position(button,x,y);
           y+=button->geometry().height();
           y+=2;//留出空余空间
       }
    }

}
void analysis::setbutton_position(QAbstractButton* button,int x,int y)
{
    int width=button->geometry().width();
    int height=button->geometry().height();
    button->setGeometry(x,y,width,height);
}
void analysis::set_shadow(QWidget *widget)
{
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(5, 5);
    shadow_effect->setColor(QColor(50, 50, 50));
    shadow_effect->setBlurRadius(8);

    widget->setGraphicsEffect(shadow_effect);

}
void analysis::remove_shadow(QWidget *widget)
{
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(5, 5);
    shadow_effect->setColor(QColor(255, 255, 255));
    shadow_effect->setBlurRadius(8);

    widget->setGraphicsEffect(shadow_effect);

}
void analysis::on_pressed()
{
    int index;
    QPushButton* button=qobject_cast<QPushButton*>(sender());
    index=findindex_button(button);
    this->child->index=index;
    this->child->place_flag=true;
    this->draw_flag=true;
    update();

}
int analysis::findindex_button(QPushButton* button)
{
    int index=0;
    for(int i=0;i<this->custom_menu->buttom_group.size();i++)
    {
        QButtonGroup* group=this->custom_menu->buttom_group[i];
        foreach(QAbstractButton* but,group->buttons())
        {
            if(but==button)
                return index;
            index++;
        }
    }
    return 0;
}
QAbstractButton* analysis::findbutton(int index)
{
    int count=0;
    for(int i=0;i<this->custom_menu->buttom_group.size();i++)
    {
        QButtonGroup* group=this->custom_menu->buttom_group[i];
        foreach(QAbstractButton* but,group->buttons())
        {
            if(count==index)
                return but;
            count++;
        }
    }
    return nullptr;
}
QPoint* analysis::transform_position(QWidget* w1,QWidget* w2,QPoint* pos)
{
    int x;
    int y;
    x=w2->mapFromGlobal(w1->mapToGlobal(*pos)).x();
    y=w2->mapFromGlobal(w1->mapToGlobal(*pos)).y();
    return new QPoint(x,y);

}
void analysis::keyPressEvent(QKeyEvent *event)
{    
    if(event->key()==Qt::Key_Delete)
    {
        QString url=this->str_to_map.key(project->currentItem());
        for(int i=0;i<this->url_group.size();i++)
            if(this->url_group[i].indexOf(url)!=-1)
            {
                this->mainwindow_current=this->mainwindow_group[find_with_url(url)];
                this->remove_file();
                return;
            }
        if(this->project_url.indexOf(url)!=-1)
        {
            this->current_project_id=this->project_url.indexOf(url);
            this->remove_project();
            return;
        }

    }
}
void analysis::mousePressEvent(QMouseEvent* event)
{
}
void analysis::paintEvent(QPaintEvent *)
{
    QPoint* oldpoint=new QPoint();
    QPoint* newpoint;
    QPainter painter(this);
    painter.setPen(QPen(Qt::red,2));
    if(this->draw_flag)
    {
        QRect rect=this->findbutton(this->child->index)->geometry();
        oldpoint->setX(rect.x());
        oldpoint->setY(rect.y());
        newpoint=this->transform_position(this->ui->centralWidget,this,oldpoint);
        painter.drawRect(QRect(newpoint->x(),newpoint->y(),rect.width(),rect.height()));
    }
}
void analysis::test()
{
    dialog_simu();
}
void analysis::test_simulation()
{
    if(this->mainwindow_current->check_connect()==true)
    {
        this->statr_message("current block diagram cannot perform non-real-time simulation",1000);
        return;
    }//半实物仿真不能是非实时仿真
    start_simu(false);
}
void analysis::dialog_simu()
{
    start_simu(true);
}
void analysis::start_simu(bool flag)
{   
    if(this->mainwindow_current==nullptr)
        return;
    if(this->mainwindow_current->run!=nullptr)
    {
        statr_message("please close the current run_window",1000);
        return;
    }
    if(this->mainwindow_current->check_signal()==false)
    {
        //statr_message("signal error",1000);
        this->mainwindow_current->update();
        return;
    }
    this->mainwindow_current->build_connect();
    if(this->mainwindow_current->sys_flag->main_socket_exist==true)
        this->mainwindow_current->new_socket_connect();
    dialog=new paramdialog(this,nullptr,this->mainwindow_current->sys_flag);
    if(dialog->exec())
    {
        if(this->mainwindow_current->sys_flag->main_socket_exist==true)
        {
            if(dialog->interface->connect_input->text()=="connect")
            {
                this->statr_message("connect failure",2000);
                return;
            }
        }
        QMdiSubWindow* window;
        scoll *s = new scoll(nullptr,this);
        s->setWindowTitle("实时仿真");
        s->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        if(flag)
            run=new Run_Simu(s,this->mainwindow_current->getsimulation_group(),dialog->param[0]->text().toDouble(),dialog->param[1]->text().toDouble(),true);
        else
            run=new Run_Simu(s,this->mainwindow_current->getsimulation_group(),dialog->param[0]->text().toDouble(),dialog->param[1]->text().toDouble(),false);

        if(this->mainwindow_current->check_connect()==true)
        {
            //this->mainwindow_current->send_clock->start(50);
            //this->mainwindow_current->rece_clock->start(10);
            run->real_flag=true;
        }
        else
            run->real_flag=false;
        run->window_parent=this->mainwindow_current;
        s->setWidget(run);
        window=ui->area->addSubWindow(s);
        run->loadmindindow(window);
        s->show();
        run_scoll.push_back(s);
        run_group.push_back(run);
        //this->mainwindow_current->moudle_relation();
        run->moudle_relation();
        run->realtime_simulation();
        this->mainwindow_current->init_finished_flag();
        this->run_current=run;
        run->parent=this;

        this->mainwindow_current->run=run;
    }
}
void analysis::test_algorithm()
{
    if(this->mainwindow_current==nullptr)
        return;
    algorithm* alg=new algorithm();
    alg->init(this->mainwindow_current->getsimulation_group());
    if(alg->exec())
    {
        qDebug()<<"start run";
    }
    //alg->show();
}
int analysis::message_box_main(MainWindow* window,int flag)
{
    int retu=0;
    QMessageBox * mBox = new QMessageBox(this);
    mBox->setWindowTitle(QString::fromLocal8Bit("analysis"));
    QString name=window->name;
    name+=".ifg";
    if(window->save_open==false)
        mBox->setText("Whether to save file");
    else
        mBox->setText("Whether to save file to"+name);
    if(flag==0)
    {
        mBox->setStandardButtons(QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No|QMessageBox::StandardButton::Cancel);
        mBox->setButtonText(QMessageBox::StandardButton::Cancel,"Cancel");
    }
    else if(flag==1)
    {
        mBox->setStandardButtons(QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
    }
    mBox->setButtonText(QMessageBox::StandardButton::Yes,"save");
    mBox->setButtonText(QMessageBox::StandardButton::No,"not save");
    mBox->exec();
    QMessageBox::StandardButton ret = mBox->standardButton(mBox->clickedButton());
    if (mBox != nullptr)
    {
        delete mBox;
    }
    switch(ret)
    {
        case QMessageBox::StandardButton::Yes:
    {
        window->save();
    };break;
        case QMessageBox::StandardButton::No:
    {
    };break;
        case QMessageBox::StandardButton::Cancel:
    {
        retu=1;
    };break;
    }
    return retu;
}
int  analysis::custom_message_box(QString title,QStringList lis)
{
    int retu=0;
    QMessageBox * mBox = new QMessageBox(this);
    mBox->setText(title);
    if(lis.size()==2)
    {
        mBox->setStandardButtons(QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
    }
    else if(lis.size()==3)
    {
        mBox->setStandardButtons(QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No|QMessageBox::StandardButton::Cancel);
        mBox->setButtonText(QMessageBox::StandardButton::Cancel,lis[2]);
    }
    mBox->setButtonText(QMessageBox::StandardButton::Yes,lis[0]);
    mBox->setButtonText(QMessageBox::StandardButton::No,lis[1]);
    mBox->exec();
    QMessageBox::StandardButton ret = mBox->standardButton(mBox->clickedButton());
    if (mBox != nullptr)
    {
        delete mBox;
    }
    switch(ret)
    {
        case QMessageBox::StandardButton::Yes:
    {
        retu=1;
    };break;
        case QMessageBox::StandardButton::No:
    {
        retu=2;
    };break;
        case QMessageBox::StandardButton::Cancel:
    {
        retu=3;
    };break;
    }
    return retu;

}
void analysis::closeEvent(QCloseEvent *event)
{
    int flag=0;
    for(int i=0;i<this->mainwindow_group.size();i++)
    {
        if(this->mainwindow_group[i]->modify==true)
        {
            flag=1;
            break;
        }
    }
    if(flag==0)//所有文件都已经保存过
    {
        event->accept();
        return;
    }
    int way=this->close_acess(0);
    if(way==0)
    {
        for(int i=0;i<this->mainwindow_group.size();i++)
        {
            this->mainwindow_current=this->mainwindow_group[i];
            if(this->mainwindow_group[i]->modify==true)
            {
                this->mainwindow_group[i]->save();
                this->mainwindow_group[i]->modify=false;
            }
        }
        event->accept();
    }
    else if(way==1)
    {
        for(int i=0;i<this->mainwindow_group.size();i++)
        {
            this->mainwindow_current=this->mainwindow_group[i];
            if(this->mainwindow_group[i]->modify==true)
            {
                this->message_box_main(this->mainwindow_group[i],1);
                this->mainwindow_group[i]->modify=false;
            }
        }
        event->accept();
    }
    else if(way==2)
    {
        event->ignore();
    }
}
int analysis::close_acess(int index)//关闭窗口时访问
{
    QMessageBox * mBox = new QMessageBox(this);
    if(index==0)
    {
        mBox->setWindowTitle(QString::fromLocal8Bit("analysis"));
        mBox->setText(QString::fromLocal8Bit("Whether to save all files"));
    }
    else if(index==1)
    {
        mBox->setWindowTitle(QString::fromLocal8Bit("simulation"));
        mBox->setText(QString::fromLocal8Bit("Whether to save data"));
    }
    mBox->setStandardButtons(QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No|QMessageBox::StandardButton::Cancel);
    if(index==0)
    {
        mBox->setButtonText(QMessageBox::StandardButton::Yes,"save to all");
        mBox->setButtonText(QMessageBox::StandardButton::No,"not save all");
    }
    else if(index==1)
    {
        mBox->setButtonText(QMessageBox::StandardButton::Yes,"save");
        mBox->setButtonText(QMessageBox::StandardButton::No,"not save");
    }
    mBox->setButtonText(QMessageBox::StandardButton::Cancel,"Cancel");
    mBox->exec();
    QMessageBox::StandardButton ret = mBox->standardButton(mBox->clickedButton());
    if (mBox != nullptr)
    {
        delete mBox;
    }
    switch(ret)
    {
        case QMessageBox::StandardButton::Yes:return 0;
        case QMessageBox::StandardButton::No:return 1;
        case QMessageBox::StandardButton::Cancel:return 2;
    default:return -1;
    }
}
void analysis::save_graph_date()//保存仿真运行图表数据,对多有图表进行访问
{
    for(int i=0;i<this->run_current->graph_name.size();i++)
    {
        if(this->run_current->save_complete[i]==false)
        {
            this->run_current->current_graph_id=i;
            this->save_graph(i);
        }
    }
}
void analysis::save_graph(int index)//访问单个图表
{
    QMessageBox * mBox = new QMessageBox(this);
    mBox->setWindowTitle(QString::fromLocal8Bit("analysis"));
    QString name=this->run_current->graph_name[index];
    mBox->setText("Whether to save "+name+" data");
    mBox->setStandardButtons(QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
    mBox->setButtonText(QMessageBox::StandardButton::Yes,"save");
    mBox->setButtonText(QMessageBox::StandardButton::No,"not save");
    mBox->exec();
    QMessageBox::StandardButton ret = mBox->standardButton(mBox->clickedButton());
    if (mBox != nullptr)
    {
        delete mBox;
    }

    switch(ret)
    {
        case QMessageBox::StandardButton::Yes:
    {
        this->run_current->save_complete[index]=true;
        if(this->run_current->url[index]!="")
            this->run_current->save_data(new QFile(this->run_current->url[index]),index);
        else
            this->save_as(1);
        this->run_current->statusBar_show();
    };break;
    }
}
void analysis::write_project()
{
    QFile* file=new QFile(this->project_url[this->current_project_id]);
    if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"error";
        return;
    }
    QDataStream ds(file);
    ds<<this->url_group[current_project_id];
    file->close();
}
void analysis::addfile(QString url)
{
    if(this->url_group[current_project_id].indexOf(url)==-1)
    {
        this->url_group[current_project_id].push_back(url);
        QTreeWidgetItem* item=new QTreeWidgetItem(*this->str_to_map.find(this->project_url[current_project_id]),QStringList(this->url_to_name(url)[0]));
        this->str_to_map.insert(url,item);
        //qDebug()<<url;
        write_project();
        this->mainwindow_current=this->mainwindow_group[find_with_url(url)];
        this->mainwindow_current->project_url=this->project_url[this->current_project_id];//该文件已存在于工程中，不需要再次加入工程
        this->mainwindow_current->save_as(new QFile(url),1);
        //qDebug()<<this->mainwindow_current->project_url;

    }
}
void analysis::remove_file_project(int way)
{
    QString url=this->str_to_map.key(project->currentItem());
    for(int i=0;i<this->url_group.size();i++)
        if(this->url_group[i].indexOf(url)!=-1)
        {
            QStringList lis;
            QString str;
            this->current_project_id=i;
            str="Whether to remove the "+url_to_name(url)[0]+" file from the "+url_to_name(project_url[i])[0]+" project";
            lis.push_back("yes");
            lis.push_back("no");
            if(this->custom_message_box(str,lis)==1)
            {
                this->removefile(url,0);
            }
            break;
        }
    for(int i=0;i<this->project_url.size();i++)
        if(this->project_url.indexOf(url)!=-1)
        {
            QStringList lis;
            QString str;
            this->current_project_id=i;
            str="Whether to remove the "+url_to_name(url)[0]+" project";
            lis.push_back("yes");
            lis.push_back("no");
            if(this->custom_message_box(str,lis)==1)
            {
                removeproject(i);
            }
            break;
        }
    //qDebug()<<this->name_group.indexOf(name);
}
void analysis::remove_file()
{
    QStringList lis;
    QString str;
    QString url=this->url_group[current_project_id][current_file_id];
    qDebug()<<current_file_id;
    str="Whether to remove the "+url_to_name(url)[0]+" file from the "+url_to_name(project_url[current_project_id])[0]+" project";
    lis.push_back("yes");
    lis.push_back("no");
    if(this->custom_message_box(str,lis)==1)
    {
        current_file_id--;
        if(current_file_id==-1)
            current_file_id=0;
        qDebug()<<current_file_id;
        this->removefile(url,0);
    }
}
void analysis::removefile(QString url,int way)
{
    if(this->url_group[current_project_id].indexOf(url)!=-1)
    {
        if(way==0)
        {
            project->removeItemWidget(*(this->str_to_map.find(url)),0);
            //(*this->str_to_map.find(url))->parent()->removeChild(*this->str_to_map.find(url));
            delete *this->str_to_map.find(url);
            this->str_to_map.remove(url);
        }
        //this->url_group[current_project_id].removeAt(this->url_group[current_project_id].indexOf(url));
        this->url_group[current_project_id].removeOne(url);
        write_project();
        int index=find_with_url(url);
        if(index!=-1)
        {
            this->mainwindow_group[index]->project_url="-1";//将文件从所在工程中移除
            this->mainwindow_group[index]->save_as(new QFile(url),1);
            emit this->scoll_group[index]->close();
        }
    }
}
void analysis::remove_project()
{
    QStringList lis;
    QString str;
    QString url=this->project_url[current_project_id];
    str="Whether to remove the "+url_to_name(url)[0]+" project";
    lis.push_back("yes");
    lis.push_back("no");
    if(this->custom_message_box(str,lis)==1)
    {
        removeproject(current_project_id);
    }
}
void analysis::removeproject(int index)
{
    QString url=this->project_url[index];
    this->project_url.removeAt(index);
    this->url_group.removeAt(index);
    QTreeWidgetItem* parent=*this->str_to_map.find(url);
    int count=parent->childCount();
    for(int i=0;i<count;i++)
    {
        QString name=this->str_to_map.key(parent->child(0));
        int index1=find_with_url(name);
        //this->scoll_group[index]->closeEvent();
        if(index1!=-1)
            emit this->scoll_group[index1]->close();
        delete parent->child(0);
    }
    project->removeItemWidget(parent,0);//注意，treeview移除前要先从父级树上移除
    delete parent;
}
void analysis::whitch_project(QString url)
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("选择工程"),"",tr("Config Files (*.pro)"));
    if(fileName.isNull())
        return;
    if(this->project_url.indexOf(fileName)!=-1)
    {
        this->current_project_id=this->project_url.indexOf(fileName);
        this->addfile(url);
    }
    else
    {
        QFile* file=new QFile(fileName);
        if(!file->open(QIODevice::Append | QIODevice::Text))
        {
            qDebug()<<"error";
            return;
        }
        QDataStream ds(file);
        QStringList lis;
        lis.push_back(url);
        ds<<lis;
        file->close();
        int index=find_with_url(url);
        this->mainwindow_group[index]->project_url=fileName;
        this->mainwindow_group[index]->save_as(new QFile(url),1);
    }

}
int analysis::find_with_url(QString url)
{
    for(int i=0;i<this->mainwindow_group.size();i++)
        if(this->mainwindow_group[i]->url==url)
            return i;
    return -1;
}
void analysis::create_empty_project(QString fileName)
{
    QFile* file=new QFile(fileName);
    if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"error";
        return;
    }
    file->close();
}
QString analysis::exist_project(QString fileName)
{
    QFile* file=new QFile(fileName);
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"error";
        return "false";
    }
    QStringList url;
    QDataStream ds(file);
    ds>>url;
    file->close();
    if(url.size()!=0)
        return url[0];
    else
        return "false";
}
void analysis::update_tree(QString name)
{
    this->custom_menu->pop_up_menu->move(cursor().pos());
    this->custom_menu->pop_up_menu->show();

    if(this->project_url.indexOf(name)!=-1)
    {
        this->current_project_id=this->project_url.indexOf(name);
        return;
    }
    for(int i=0;i<this->url_group.size();i++)
        if(this->url_group[i].indexOf(name)!=-1)
        {
            this->current_project_id=i;
            this->current_file_id=this->url_group[i].indexOf(name);
            int index=this->find_with_url(name);//修改当前组态窗口
            this->mainwindow_current=this->mainwindow_group[index];
            return;
        }
}
int analysis::run_to_mainwindow(Run_Simu* run)
{
    return this->run_group.indexOf(run);
}
QDataStream &operator<<(QDataStream& output, QStringList& str)
{
    //output<<MainWindow::thirteen(str.size());
    for(int i=0;i<str.size();i++)
        output<<str[i];
    return output;
}
QDataStream &operator>>(QDataStream& input, QStringList& str)
{
    QString string;
    while(1)
    {
        input>>string;
        if(string==""||string=="-1")
            break;
        str<<string;
    }
    return input;
}
scoll::scoll(QWidget *pare,analysis* par):QScrollArea(pare),parent(par)
{
}
void scoll::closeEvent(QCloseEvent *event)
{
    //scoll* Scoll=dynamic_cast<scoll*>(sender());
    if(this->parent->scoll_group.indexOf(this)!=-1)
    {
        int index=this->parent->scoll_group.indexOf(this);
        if(this->parent->mainwindow_group[index]->modify==true&&this->parent->message_box_main(this->parent->mainwindow_group[index],0)==1)
        {
            event->ignore();
        }
        else
        {            
            this->parent->ui->area->removeSubWindow(this->parent->scoll_group[index]);
            this->parent->scoll_group.removeAt(index);
            //emit this->parent->mainwindow_group[index]->close();
            delete this->parent->mainwindow_group[index];
            this->parent->mainwindow_group.removeAt(index);
            this->parent->mainwindow_current=nullptr;
            QMdiSubWindow* mid=this->parent->mid_group[index];
            this->parent->mid_group.removeAt(index);
            mid->close();
            event->accept();
            //delete this;
            //qDebug()<<1;
        }
    }
    else
    {
        int index=this->parent->run_scoll.indexOf(this);
        if(this->parent->run_group[index]->getstate()==true)
            this->parent->run_group[index]->mDataTimer.stop();
        int way=this->parent->close_acess(1);
        if(way==2)
        {
            event->ignore();
            if(this->parent->run_group[index]->getstate()==true)
                this->parent->run_group[index]->mDataTimer.start(10);
            return;
        }
        else if(way==1||way==0)
        {
            if(way==0)
                this->parent->run_group[index]->save_graph_date();
            this->parent->ui->area->removeSubWindow(this->parent->run_scoll[index]);
            this->parent->run_scoll.removeAt(index);
            for(int i=0;i<this->parent->mainwindow_group.size();i++)
                if(this->parent->mainwindow_group[i]->run==this->parent->run_group[index])
                {
                    this->parent->mainwindow_group[i]->run=nullptr;
                    this->parent->mainwindow_group[i]->disconnect_input(0);
                    if(this->parent->mainwindow_group[i]->sys_flag->socket_main!=nullptr)
                    {
                        this->parent->mainwindow_group[i]->sys_flag->socket_main->disconnectFromHost();
                    }
                    break;
                }

            delete this->parent->run_group[index];
            this->parent->run_group.removeAt(index);
        }
    }
}
void analysis::export_algorithm()
{
    if(this->mainwindow_current==nullptr)
        return;
    QString savefile=QFileDialog::getSaveFileName(this,tr("export algorithm"),"",tr("Config Files (*.alg)"));
    QString str="";
    if(!savefile.isNull())
    {
        QFile* file=new QFile(savefile);
        if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug()<<"error";
            return;
        }
        struct moudle_relation moudlee;

        for(int i=0;i<this->mainwindow_current->getsimulation_group()->group.size();i++)
        {
            Simulation_Moudle* moudle=this->mainwindow_current->getsimulation_group()->group[i];
            for(int m=0;m<moudle->output.size();m++)
            {
                moudle_param* param=moudle->output[m];
                for(int n=0;n<param->connect_line.size();n++)
                {
                    Line* linee=param->connect_line[n];
                    for(int j=0;j<linee->endbutton.size();j++)
                    {
                        moudlee.moudle=this->mainwindow_current->getsimulation_group()->findwithbutton(linee->endbutton[j]);
                        moudlee.index=linee->endindex[j];
                        moudle->output[m]->next.push_back(moudlee);
                    }
                }
            }
        }

        str=str+"!"+QString::number(this->mainwindow_current->getsimulation_group()->group.size());
        for(int i=0;i<this->mainwindow_current->getsimulation_group()->group.size();i++)
        {
            Simulation_Moudle* moudle=this->mainwindow_current->getsimulation_group()->group[i];
            str=str+"!"+QString::number(moudle->param.size());
            for(int j=0;j<moudle->param.size();j++)
                str=str+"!"+QString::number(moudle->param[j]);
            str=str+"!"+QString::number(moudle->index);
            str=str+"!"+QString::number(moudle->id);
            str=str+"!"+moudle->name;

            str=str+"!"+QString::number(moudle->input_size);
            str=str+"!"+QString::number(moudle->output_size);

            str=str+"!"+QString::number(moudle->output.size());
            for(int j=0;j<moudle->output.size();j++)
            {
                str=str+"!"+QString::number(moudle->output[j]->next.size());
                for(int m=0;m<moudle->output[j]->next.size();m++)
                {
                    str=str+"!"+QString::number(moudle->output[j]->next[m].moudle->id);
                    str=str+"!"+QString::number(moudle->output[j]->next[m].index);
                }
            }

            if(moudle->index==38)
            {
                str=str+"!"+QString::number(moudle->bind_interface->input_flag);
                str=str+"!"+QString::number(moudle->bind_interface->input_ip.size());
                for(int j=0;j<moudle->bind_interface->input_ip.size();j++)
                    str=str+"!"+QString::number(moudle->bind_interface->input_ip[j]);
                str=str+"!"+QString::number(moudle->bind_interface->input_port);

                str=str+"!"+QString::number(moudle->bind_interface->output_flag);
                str=str+"!"+QString::number(moudle->bind_interface->output_ip.size());
                for(int j=0;j<moudle->bind_interface->output_ip.size();j++)
                    str=str+"!"+QString::number(moudle->bind_interface->output_ip[j]);
                str=str+"!"+QString::number(moudle->bind_interface->output_port);
            }
            else if(moudle->index==39)
            {
                str=str+"!"+QString::number(moudle->tag_bind->input_flag);
                str=str+"!"+moudle->tag_bind->input_tag;
                str=str+"!"+QString::number(moudle->tag_bind->output_flag);
                str=str+"!"+moudle->tag_bind->output_tag;
            }
        }
        QByteArray byt=str.toLatin1();
        file->write(byt);
        file->close();
    }
}
