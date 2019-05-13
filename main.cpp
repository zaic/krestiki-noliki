#include "main.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

void MyClass::cppSlot(const int row, const int col) {
    qDebug() << "Called the C++ slot with value:" << row << col;

    if (row < 0 || row > 2 || col < 0 || col > 2) return ;
    if (m_cells[row][col] != CellState::Empty || m_nextTurnState == CellState::Empty) return ;

    m_cells[row][col] = m_nextTurnState;

    QMetaObject::invokeMethod(&m_rootObject, "switchCell", Q_ARG(QVariant, row), Q_ARG(QVariant, col), Q_ARG(QVariant, static_cast<int>(m_nextTurnState)));

    for (int idx = 0; idx < 3; ++idx) {
        if ((m_cells[idx][0] == m_nextTurnState && m_cells[idx][1] == m_nextTurnState && m_cells[idx][2] == m_nextTurnState)
            || (m_cells[0][idx] == m_nextTurnState && m_cells[1][idx] == m_nextTurnState && m_cells[2][idx] == m_nextTurnState)
            || (m_cells[0][0] == m_nextTurnState && m_cells[1][1] == m_nextTurnState && m_cells[2][2] == m_nextTurnState)
            || (m_cells[0][2] == m_nextTurnState && m_cells[1][1] == m_nextTurnState && m_cells[2][0] == m_nextTurnState)) {
            QMetaObject::invokeMethod(&m_rootObject, "endGame", Q_ARG(QVariant, m_nextTurnState == CellState::Krestik ? "Krestiki" : "Noliki"));
            m_nextTurnState = CellState::Empty;
            return ;
        }
    }

    m_nextTurnState = static_cast<CellState>((3 - static_cast<int>(m_nextTurnState)) % 3);
}

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    auto it = engine.rootObjects().first();
    MyClass myClass(*it);
    QObject::connect(it, SIGNAL(tapOnCell(int, int)), &myClass, SLOT(cppSlot(int, int)));

    return app.exec();
}
