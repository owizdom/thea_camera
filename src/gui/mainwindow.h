#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QSlider>
#include <QProgressBar>
#include <QTextEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QScrollArea>
#include <QTabWidget>
#include <QStatusBar>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QDir>
#include <QStandardPaths>

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QSlider;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startCamera();
    void stopCamera();
    void capturePhoto();
    void startRecording();
    void stopRecording();
    void updateFrame();
    void onModeChanged();
    void onResolutionChanged();
    void onFPSChanged();
    void onQualityChanged();
    void onWideModeToggled();
    void openSettings();
    void about();

private:
    void setupMenuBar();
    void setupStatusBar();
    void setupCamera();
    void setupVideoWriter();
    void processFrame(cv::Mat &frame);
    void savePhoto(const cv::Mat &frame);
    void saveVideo();
    void updateStatusBar();
    void createDirectories();
    
    Ui::MainWindow *ui;
    
    // Camera and video
    cv::VideoCapture *camera;
    cv::VideoWriter *videoWriter;
    QTimer *timer;
    
    // State variables
    bool isCameraRunning;
    bool isRecording;
    int photoCount;
    int videoCount;
    QString photosDir;
    QString videosDir;
    QString currentVideoFile;
    
    // Camera settings
    int currentWidth;
    int currentHeight;
    int currentFPS;
    int currentQuality;
    bool wideMode;
    QString currentMode;
};

#endif // MAINWINDOW_H
