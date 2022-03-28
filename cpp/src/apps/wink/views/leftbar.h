#ifndef LEFTBAR_H
#define LEFTBAR_H

#include <QWidget>

class Avatar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString image READ getImage WRITE setImage NOTIFY imageChanged)
public:
    explicit Avatar(QWidget* parent = nullptr);
    ~Avatar();

    const QString& getImage() const;
    
public slots:
    void setImage(const QString& image);

signals:
    void imageChanged(const QString& image);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    QString m_image;
    QImage m_imageDevice;
};

class QListView;
class LeftBar : public QWidget
{
    Q_OBJECT

public:
    explicit LeftBar(QWidget* parent = nullptr);
    ~LeftBar();

    Avatar* avatar() const;

protected:
    void paintEvent(QPaintEvent*) override;

private slots:
    void onItemclicked(const QModelIndex& index);
    void onActivedChanged(const QModelIndex& index);

private:
    Avatar* m_avatar;
    QListView* m_listView;
};

#endif // LEFTBAR_H
