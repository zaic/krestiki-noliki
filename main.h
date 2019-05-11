#pragma once

#include <QtCore/QDebug>
#include <QQuickItem>

enum class CellState { Empty, Krestik, Nolik };

class MyClass : public QObject {
    Q_OBJECT

public:
    MyClass(QObject& rootObject): m_rootObject(rootObject) { memset(m_cells, 0, sizeof(m_cells)); }

public slots:
    void cppSlot(const int row, const int col);

private:
    QObject& m_rootObject;
    CellState m_cells[3][3];
    CellState m_nextTurnState = CellState::Krestik;
};
