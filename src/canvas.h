#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <QWidget>

class Canvas : public QWidget
{
public:
    /**
     * @brief Constructor de clase Canvas.
     *
     * @param parent p_parent: Ventana padre para Qt.
     */
    Canvas(QWidget* parent = 0);

protected:
    /**
     * @brief Método usado por Qt para pintar el QWidget.
     *
     * @param e p_e: Evento no usado.
     */
    void paintEvent(QPaintEvent *e) override;

private:
    /**
     * @brief Genera el "pintado" del widget. Llamado por paintEvent.
     *
     */
    void doPainting();
};

#endif                                                      // _CANVAS_H_
