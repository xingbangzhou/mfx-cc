#ifndef BIZBAR_H
#define BIZBAR_H

#include <QWidget>

class Avatar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString image READ getImage WRITE setImage NOTIFY imageChanged)
public:
    explicit Avatar(QWidget* parent = nullptr);
    ~Avatar();

    const QString& getImage() const;
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
class BizBar : public QWidget
{
    Q_OBJECT

public:
    explicit BizBar(QWidget* parent = nullptr);
    ~BizBar();

    Avatar* avatar() const;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Avatar* m_avatar;
    QListView* m_listView;
};

#endif // BIZBAR_H
