/**********************************************************************
Copyright (c)
Audi Autonomous Driving Cup. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
3.  All advertising materials mentioning features or use of this software must display the following acknowledgement: “This product includes software developed by the Audi AG and its contributors for Audi Autonomous Driving Cup.”
4.  Neither the name of Audi nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY AUDI AG AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL AUDI AG OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


**********************************************************************
* $Author:: spie#$  $Date:: 2017-05-12 09:39:39#$ $Rev:: 63110   $
**********************************************************************/

#include "stdafx.h"

#include "uswidget.h"

/*!
 * Clamp the given value.
 *
 * \tparam  T   Generic type parameter.
 * \param   value   The value.
 * \param   low     The low.
 * \param   high    The high.
 *
 * \return  clamped value
 */
template <typename T> static T CLAMP(const T& value, const T& low, const T& high)
{
    return value < low ? low : (value > high ? high : value);
}

uswidget::uswidget(QWidget *parent) : QWidget(parent)
{
    m_elapsed = 0;
    m_arcbrush = QBrush(Qt::black);
    memset(&m_usData, 0, sizeof(tUltrasonicStructSimple));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(50);
}

void uswidget::animate()
{
    m_elapsed = (m_elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    update();
}

void uswidget::setDistances(int us_front_left,
                            int us_front_center_left,
                            int us_front_center,
                            int us_front_center_right,
                            int us_front_right,
                            int us_side_left,
                            int us_side_right,
                            int us_rear_center_left,
                            int us_rear_center,
                            int us_rear_center_right)
{
    m_usData.us_front_left            = CLAMP(us_front_left, 0, 50) * 2;
    m_usData.us_front_center_left     = CLAMP(us_front_center_left, 0, 50) * 2;
    m_usData.us_front_center          = CLAMP(us_front_center, 0, 50) * 2;
    m_usData.us_front_center_right    = CLAMP(us_front_center_right, 0, 50) * 2;
    m_usData.us_front_right           = CLAMP(us_front_right, 0, 50) * 2;

    m_usData.us_side_left     = CLAMP(us_side_left, 0, 50) * 2;
    m_usData.us_side_right    = CLAMP(us_side_right, 0, 50) * 2;

    m_usData.us_rear_center_left  = CLAMP(us_rear_center_left, 0, 50) * 2;
    m_usData.us_rear_center       = CLAMP(us_rear_center, 0, 50) * 2;
    m_usData.us_rear_center_right = CLAMP(us_rear_center_right, 0, 50) * 2;
}

void uswidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    paint(&painter, event);
    painter.end();
}

void uswidget::paint(QPainter *painter, QPaintEvent *event)
{
    painter->fillRect(event->rect(), Qt::white);

    m_canvas_width = event->rect().width();
    m_canvas_height = event->rect().height();
    QPoint center(m_canvas_width/2, m_canvas_height/2);


    drawFilledArc(painter, center, 28, 24, m_usData.us_front_right); // front right
    drawFilledArc(painter, center, 53, 24, m_usData.us_front_center_right); // front center right
    drawFilledArc(painter, center, 78, 24, m_usData.us_front_center); // front center
    drawFilledArc(painter, center, 103, 24, m_usData.us_front_center_left);// front center left
    drawFilledArc(painter, center, 128, 24, m_usData.us_front_left);// front left

    drawFilledArc(painter, center, -15, 29, m_usData.us_side_right); // side right
    drawFilledArc(painter, center, 165, 29, m_usData.us_side_left); // side left

    drawFilledArc(painter, center, 225, 29, m_usData.us_rear_center_left); // rear center left
    drawFilledArc(painter, center, 255, 29, m_usData.us_rear_center); // rear center
    drawFilledArc(painter, center, 285, 29, m_usData.us_rear_center_right); // rear center right

    painter->setBrush(QBrush(Qt::black));
    int rwidth = m_canvas_width / 10;
    int rheight = m_canvas_height / 5;
    QRectF car(m_canvas_width/2 - rwidth/2, m_canvas_height/2 - rheight/2, rwidth, rheight);
    painter->drawRoundRect(car);
}

void uswidget::drawFilledArc(QPainter *painter,QPointF origin, int startAngle, int spanAngle, int fillpercentage)
{
    painter->save();

    QColor color = getGradientColor(QColor(Qt::red), QColor(Qt::green), fillpercentage);
    m_arcbrush = QBrush(color);

    // outline the arc
    QRectF maxRect(5, 5, m_canvas_width-10, m_canvas_height-10);
    maxRect.moveCenter(origin);
    painter->setPen(QPen(Qt::black));
    painter->drawPie(maxRect, startAngle * 16, spanAngle * 16);

    // fill the arc according to fillpercentage
    double scale = (double)fillpercentage / (double)100;
    QRectF distance;
    distance = QRectF(0, 0, scale * maxRect.width(), scale * maxRect.height());
    distance.moveCenter(origin);

    painter->setBrush(m_arcbrush);
    painter->drawPie(distance, startAngle * 16, spanAngle * 16);

    painter->restore();
}

QColor uswidget::getGradientColor(QColor start, QColor end, int value) // value = [0, 100]
{
    // calculate the gradient color given by fillpercentage
    int startRedVal = start.red();
    int startGreenVal = start.green();
    int startBlueVal = start.blue();

    int endRedVal = end.red();
    int endGreenVal = end.green();
    int endBlueVal = end.blue();

    double ratio = (double)value/100.0;
    int red =   (int)(ratio * endRedVal   + (1-ratio) * startRedVal);
    int green = (int)(ratio * endGreenVal + (1-ratio) * startGreenVal);
    int blue =  (int)(ratio * endBlueVal  + (1-ratio) * startBlueVal);

    QColor color(red, green, blue);

    return color;
}
