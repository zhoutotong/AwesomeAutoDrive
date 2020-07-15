// -*- mode: c++; -*-
/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2014, JSK Lab
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/o2r other materials provided
 *     with the distribution.
 *   * Neither the name of the JSK Lab nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#include "doublevaluemeter.h"
#include <OGRE/OgreMaterialManager.h>
#include <rviz/uniform_string_stream.h>
#include <OGRE/OgreTexture.h>
#include <OGRE/OgreHardwarePixelBuffer.h>
#include <QFontDatabase>
#include <QPainter>
#include <QStaticText>
#include <QTextDocument>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <jsk_topic_tools/log_utils.h>
#include <ros/package.h>
#include <std_msgs/Float64.h>



#include <QDebug>
namespace awe_visualization
{

DoubleValueMeter::DoubleValueMeter() : Display(),
                                       texture_width_(200), texture_height_(160),
                                       text_size_(14),
                                       line_width_(2),
                                       text_(""), font_(""),
                                       bg_color_(52, 101, 164, 255.0f * 0.3f),
                                       fg_color_(25, 255, 240, 255.0f * 0.8f),
                                       require_update_texture_(false),
                                       range_min(-120.0),
                                       range_max(120),
                                       left_(0),
                                       top_(0),
                                       width_(200),
                                       height_(160),
                                       value_a(0.0),
                                       value_b(0.0),
                                       label("")
{
    update_topic_property_ = new rviz::RosTopicProperty(
        "Topic", "",
        ros::message_traits::datatype<std_msgs::Float64>(),
        "hmi_msgs::steering_visualization topic to subscribe to.",
        this, SLOT(updateTopic()));
    overtake_position_properties_property_ = new rviz::BoolProperty(
        "Overtake Position Properties", false,
        "overtake position properties specified by message such as left, top and font",
        this, SLOT(updateOvertakePositionProperties()));
    overtake_color_properties_property_ = new rviz::BoolProperty(
        "Overtake Color Properties", false,
        "overtake color properties specified by message such as foreground/background color and alpha",
        this, SLOT(updateOvertakeColorProperties()));
    top_property_ = new rviz::IntProperty(
        "top", top_,
        "top position",
        this, SLOT(updateTop()));
    top_property_->setMin(0);
    left_property_ = new rviz::IntProperty(
        "left", left_,
        "left position",
        this, SLOT(updateLeft()));
    left_property_->setMin(0);
    width_property_ = new rviz::IntProperty(
        "width", width_,
        "width position",
        this, SLOT(updateWidth()));
    width_property_->setMin(0);
    height_property_ = new rviz::IntProperty(
        "height", height_,
        "height position",
        this, SLOT(updateHeight()));
    height_property_->setMin(0);
    text_size_property_ = new rviz::IntProperty(
        "text size", 12,
        "text size",
        this, SLOT(updateTextSize()));
    text_size_property_->setMin(0);
    line_width_property_ = new rviz::IntProperty(
        "line width", 2,
        "line width",
        this, SLOT(updateLineWidth()));
    line_width_property_->setMin(0);
    fg_color_property_ = new rviz::ColorProperty(
        "Foreground Color", QColor(25, 255, 240),
        "Foreground Color",
        this, SLOT(updateFGColor()));
    fg_alpha_property_ = new rviz::FloatProperty(
        "Foreground Alpha", 0.8, "Foreground Alpha",
        this, SLOT(updateFGAlpha()));
    fg_alpha_property_->setMin(0.0);
    fg_alpha_property_->setMax(1.0);

    //   bg_color_ = QColor(52, 101, 164, 255.0f * 0.3f);
    //   fg_color_ = QColor(25, 255, 240, 255.0f * 0.8f);
    bg_color_property_ = new rviz::ColorProperty(
        "Background Color", QColor(52, 101, 164),
        "Background Color",
        this, SLOT(updateBGColor()));
    bg_alpha_property_ = new rviz::FloatProperty(
        "Background Alpha", 0.3, "Background Alpha",
        this, SLOT(updateBGAlpha()));
    bg_alpha_property_->setMin(0.0);
    bg_alpha_property_->setMax(1.0);

    QFontDatabase database;
    font_families_ = database.families();
    font_property_ = new rviz::EnumProperty(
        "font", "DejaVu Sans Mono",
        "font", this,
        SLOT(updateFont()));
    for (size_t i = 0; i < font_families_.size(); i++)
    {
        font_property_->addOption(font_families_[i], (int)i);
    }

    if (!overlay_)
    {
        static int count = 0;
        rviz::UniformStringStream ss;
        ss << "DoubleValueMeterVisualizationObject" << count++;

        setPosition(left_, top_);
        overlay_.reset(new jsk_rviz_plugins::OverlayObject(ss.str()));
        overlay_->show();
    }
}

DoubleValueMeter::~DoubleValueMeter()
{
    onDisable();
    // delete overlay_;
    delete update_topic_property_;
    delete overtake_color_properties_property_;
    delete overtake_position_properties_property_;
    delete top_property_;
    delete left_property_;
    delete width_property_;
    delete height_property_;
    delete text_size_property_;
    delete line_width_property_;
    delete bg_color_property_;
    delete bg_alpha_property_;
    delete fg_color_property_;
    delete fg_alpha_property_;
    delete font_property_;
}

void DoubleValueMeter::onEnable()
{
    if (overlay_)
    {
        overlay_->show();
    }
    subscribe();
    update(0, 0);
}

void DoubleValueMeter::onDisable()
{
    if (overlay_)
    {
        overlay_->hide();
    }
    unsubscribe();
}

void DoubleValueMeter::setTopic(const QString &topic, const QString &datatype)
{
    update_topic_property_->setMessageType(datatype);
    update_topic_property_->setValue(topic);
    if (topic.length() > 0 && topic != "/")
    {
        sub_ = ros::NodeHandle().subscribe(topic.toStdString(), 1, &DoubleValueMeter::processMessage, this);
    }
}

void DoubleValueMeter::unsubscribe()
{
    sub_.shutdown();
}

void DoubleValueMeter::subscribe()
{
    std::string topic_name = update_topic_property_->getTopicStd();
    if (topic_name.length() > 0 && topic_name != "/")
    {
        sub_ = ros::NodeHandle().subscribe(topic_name, 1, &DoubleValueMeter::processMessage, this);
    }
}

void DoubleValueMeter::updateTopic()
{
    unsubscribe();
    subscribe();
}

// only the first time
void DoubleValueMeter::onInitialize()
{
    onEnable();
    updateTopic();
    updateOvertakePositionProperties();
    updateOvertakeColorProperties();
    updateTop();
    updateLeft();
    updateWidth();
    updateHeight();
    updateTextSize();
    updateFGColor();
    updateFGAlpha();
    updateBGColor();
    updateBGAlpha();
    updateFont();
    updateLineWidth();
    require_update_texture_ = true;
}

void DoubleValueMeter::update(float wall_dt, float ros_dt)
{
    if (!require_update_texture_)
    {
        return;
    }
    if (!isEnabled())
    {
        return;
    }
    if (!overlay_)
    {
        return;
    }
    if (overlay_)
    {
      overlay_->setDimensions(width_, height_);
      overlay_->setPosition(left_, top_);
    }
    overlay_->updateTextureSize(texture_width_, texture_height_);
    {
        ScopedPixelBuffer buffer = overlay_->getBuffer();
        QImage Hud = buffer.getQImage(*overlay_, bg_color_);
        QPainter painter(&Hud);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(fg_color_, line_width_ || 1, Qt::SolidLine));

        uint16_t w = overlay_->getTextureWidth();
        uint16_t h = overlay_->getTextureWidth();

        // font
        if (text_size_ != 0)
        {
            QFont font(font_.length() > 0 ? font_.c_str() : "Liberation Sans");
            font.setPointSize(text_size_);
            font.setBold(true);
            painter.setFont(font);
        }
        if (text_.length() > 0)
        {
            std::string color_wrapped_text = (boost::format("<span style=\"color: rgba(%2%, %3%, %4%, %5%)\">%1%</span>") % text_ % fg_color_.red() % fg_color_.green() % fg_color_.blue() %
                                              fg_color_.alpha())
                                                 .str();
            QStaticText static_text(
                boost::algorithm::replace_all_copy(color_wrapped_text, "\n", "<br >").c_str());
            static_text.setTextWidth(w);

            QStaticText only_wrapped_text(color_wrapped_text.c_str());
            QFontMetrics fm(painter.fontMetrics());
            QRect text_rect = fm.boundingRect(0, 0, w, h,
                                              Qt::TextWordWrap | Qt::AlignCenter,
                                              only_wrapped_text.text().remove(QRegExp("<[^>]*>")));

            // painter.drawStaticText((w - text_rect.width()) / 2.0f,
            //                        (h) / 2.0f + text_rect.height() / 2.0f - 5.0f,
            //                        static_text);
        }

        qreal arcWidth = 10;
        QRectF rectangle(Hud.rect());
        qreal cutLength = 40;

        rectangle.setWidth(Hud.rect().width() - cutLength);
        rectangle.setHeight(Hud.rect().width() - cutLength);
        rectangle.setX(cutLength);
        rectangle.setY(cutLength);

        int startAngle = -30 * 16;
        int spanAngle = 240 * 16;

        QPolygonF firstTriAngle;
        QPolygonF secondTriAngle;
        QVector<QPointF> vec;
        vec << QPointF(0, 0) << QPointF(-5, 10) << QPointF(5, 10);
        for (int i = 0; i < vec.size(); i++)
        {
            firstTriAngle.append(vec.at(i) + QPointF(w / 2.0, arcWidth + cutLength));
        }

        vec.clear();
        vec << QPointF(0, 0) << QPointF(-5, -10) << QPointF(5, -10);
        for (int i = 0; i < vec.size(); i++)
        {
            secondTriAngle.append(vec.at(i) + QPointF(w / 2.0, -arcWidth + cutLength));
        }

        qreal angb = (value_b - range_min) / (range_max - range_min) * 240.0 - 120.0;
        qreal anga = (value_a - range_min) / (range_max - range_min) * 240.0 - 120.0;


        QPen pen(painter.pen());
        //    绘制内环指针
        painter.setBrush(QBrush(Qt::black));
        pen.setWidth(1);
        painter.setPen(pen);
        painter.translate(w / 2.0, h / 2.0);
        painter.rotate(angb);
        painter.translate(-w / 2.0, -h / 2.0);
        painter.drawPolygon(firstTriAngle);
        painter.translate(w / 2.0, h / 2.0);
        painter.rotate(-angb);
        painter.translate(-w / 2.0, -h / 2.0);

        //    绘制外环指针
        painter.setBrush(QBrush(Qt::green));
        painter.translate(w / 2.0, h / 2.0);
        painter.rotate(anga);
        painter.translate(-w / 2.0, -h / 2.0);
        painter.drawPolygon(secondTriAngle);
        painter.translate(w / 2.0, h / 2.0);
        painter.rotate(-anga);
        painter.translate(-w / 2.0, -h / 2.0);

        pen.setWidth(arcWidth);
        painter.setPen(pen);
        painter.drawArc(rectangle, startAngle, spanAngle);

        // devide line
        int devideLineWidth = 5;
        pen.setWidth(devideLineWidth);
        painter.setPen(pen);
        painter.drawLine(w / 2.0 - 30, h / 2.0, w / 2.0 + 30, h / 2.0);

        // value display
        QString atext_ = QString::number(value_a, 'f', 2);
        QFontMetrics fm(painter.fontMetrics());
        QRect text_recta = fm.boundingRect(0, 0, w, h,
                                          Qt::TextWordWrap | Qt::AlignCenter,
                                          atext_);

        QStaticText staticTexta(atext_);
        painter.drawStaticText(QPointF((w - text_recta.width()) / 2.0f,
                                       (h - devideLineWidth) / 2.0 - text_recta.height()),
                               staticTexta);

        
        QString btext_ = QString::number(value_b, 'f', 2);
        QRect text_rectb = fm.boundingRect(0, 0, w, h,
                                    Qt::TextWordWrap | Qt::AlignCenter,
                                    btext_);
        QStaticText staticTextb(btext_);
        painter.drawStaticText(QPointF((w - text_rectb.width()) / 2.0f,
                                       (h + devideLineWidth) / 2.0),
                               staticTextb);

        QRect text_rect_label = fm.boundingRect(0, 0, w, h,
                                    Qt::TextWordWrap | Qt::AlignCenter,
                                    label);
        QStaticText staticTextLabel(label);
        painter.drawStaticText(QPointF((w - text_rect_label.width()) / 2.0f,
                                       (h * 7.0 / 10.0)),
                               staticTextLabel);

        painter.end();
    }
    overlay_->setDimensions(overlay_->getTextureWidth(), overlay_->getTextureHeight());
    require_update_texture_ = false;
}

void DoubleValueMeter::updateData(const DoubleValueMeterParamConstPtr &param)
{
    processMessage(param);
}

void DoubleValueMeter::processMessage(const DoubleValueMeterParamConstPtr &msg)
{
    if (!isEnabled())
    {
        return;
    }
    if (!overlay_)
    {
        static int count = 0;
        rviz::UniformStringStream ss;
        ss << "DoubleValueMeterVisualizationObject" << count++;
        overlay_.reset(new jsk_rviz_plugins::OverlayObject(ss.str()));
        overlay_->show();
    }
    if (overlay_)
    {
        overlay_->show();
    }

    // store message for update method
    range_max = msg->max;
    range_min = msg->min;
    value_a = msg->val_a;
    value_b = msg->val_b;
    label = QString::fromStdString(msg->label);
    // if (!overtake_position_properties_)
    // {
    //     // texture_width_ = 200;//msg->width;
    //     // texture_height_ = 200;//msg->height;
    //     text_size_ = 10; //msg->text_size;
    //                      // left_ = 0;//msg->left;
    //                      // top_ = 0;//msg->top;
    // }
    // if (!overtake_color_properties_)
    // {

    //     //   bg_color_ = QColor(52, 101, 164, 255.0f * 0.3f);
    //     //   fg_color_ = QColor(25, 255, 240, 255.0f * 0.8f);
    //     // bg_color_ = QColor(msg->bg_color.r * 255.0,
    //     //                    msg->bg_color.g * 255.0,
    //     //                    msg->bg_color.b * 255.0,
    //     //                    msg->bg_color.a * 255.0);
    //     // fg_color_ = QColor(msg->fg_color.r * 255.0,
    //     //                    msg->fg_color.g * 255.0,
    //     //                    msg->fg_color.b * 255.0,
    //     //                    msg->fg_color.a * 255.0);
    //     // font_ = msg->font;
    //     line_width_ = 100; //msg->line_width;
    // }
    if (overlay_)
    {
        overlay_->setPosition(left_, top_);
    }
    require_update_texture_ = true;
}

void DoubleValueMeter::updateOvertakePositionProperties()
{

    if (!overtake_position_properties_ &&
        overtake_position_properties_property_->getBool())
    {
        updateTop();
        updateLeft();
        updateWidth();
        updateHeight();
        updateTextSize();
        require_update_texture_ = true;
    }
    overtake_position_properties_ = overtake_position_properties_property_->getBool();
    if (overtake_position_properties_)
    {
        top_property_->show();
        left_property_->show();
        width_property_->show();
        height_property_->show();
        text_size_property_->show();
    }
    else
    {
        top_property_->hide();
        left_property_->hide();
        width_property_->hide();
        height_property_->hide();
        text_size_property_->hide();
    }
}

void DoubleValueMeter::updateOvertakeColorProperties()
{
    if (!overtake_color_properties_ &&
        overtake_color_properties_property_->getBool())
    {
        // read all the parameters from properties
        updateFGColor();
        updateFGAlpha();
        updateBGColor();
        updateBGAlpha();
        updateFont();
        updateLineWidth();
        require_update_texture_ = true;
    }
    overtake_color_properties_ = overtake_color_properties_property_->getBool();
    if (overtake_color_properties_)
    {
        fg_color_property_->show();
        fg_alpha_property_->show();
        bg_color_property_->show();
        bg_alpha_property_->show();
        line_width_property_->show();
        font_property_->show();
    }
    else
    {
        fg_color_property_->hide();
        fg_alpha_property_->hide();
        bg_color_property_->hide();
        bg_alpha_property_->hide();
        line_width_property_->hide();
        font_property_->hide();
    }
}

void DoubleValueMeter::updateTop()
{
    top_ = top_property_->getInt();
    if (overtake_position_properties_)
    {
        require_update_texture_ = true;
    }
}

void DoubleValueMeter::updateLeft()
{
    left_ = left_property_->getInt();
    if (overtake_position_properties_)
    {
        require_update_texture_ = true;
    }
}

void DoubleValueMeter::updateWidth()
{
    texture_width_ = width_property_->getInt();
    if (overtake_position_properties_)
    {
        require_update_texture_ = true;
    }
}

void DoubleValueMeter::updateHeight()
{
    texture_height_ = height_property_->getInt();
    if (overtake_position_properties_)
    {
        require_update_texture_ = true;
    }
}

void DoubleValueMeter::updateTextSize()
{
    text_size_ = text_size_property_->getInt();
    if (overtake_position_properties_)
    {
        require_update_texture_ = true;
    }
}

void DoubleValueMeter::updateBGColor()
{
    QColor c = bg_color_property_->getColor();
    bg_color_.setRed(c.red());
    bg_color_.setGreen(c.green());
    bg_color_.setBlue(c.blue());
    if (overtake_color_properties_)
    {
        require_update_texture_ = true;
    }
}

void DoubleValueMeter::updateBGAlpha()
{
    bg_color_.setAlpha(bg_alpha_property_->getFloat() * 255.0);
    if (overtake_color_properties_)
    {
        require_update_texture_ = true;
    }
}

void DoubleValueMeter::updateFGColor()
{
    QColor c = fg_color_property_->getColor();
    fg_color_.setRed(c.red());
    fg_color_.setGreen(c.green());
    fg_color_.setBlue(c.blue());
    if (overtake_color_properties_)
    {
        require_update_texture_ = true;
    }
}

void DoubleValueMeter::updateFGAlpha()
{
    fg_color_.setAlpha(fg_alpha_property_->getFloat() * 255.0);
    if (overtake_color_properties_)
    {
        require_update_texture_ = true;
    }
}

void DoubleValueMeter::updateFont()
{
    int font_index = font_property_->getOptionInt();
    if (font_index < font_families_.size())
    {
        font_ = font_families_[font_index].toStdString();
    }
    else
    {
        ROS_FATAL("Unexpected error at selecting font index %d.", font_index);
        return;
    }
    if (overtake_color_properties_)
    {
        require_update_texture_ = true;
    }
}

void DoubleValueMeter::updateLineWidth()
{
    line_width_ = line_width_property_->getInt();
    if (overtake_color_properties_)
    {
        require_update_texture_ = true;
    }
}

bool DoubleValueMeter::isInRegion(int x, int y)
{
    return (top_ < y && top_ + texture_height_ > y &&
            left_ < x && left_ + texture_width_ > x);
}

void DoubleValueMeter::movePosition(int x, int y)
{
    top_ = y;
    left_ = x;
}

void DoubleValueMeter::setPosition(int x, int y)
{
    top_property_->setValue(y);
    left_property_->setValue(x);
    top_ = y;
    left_ = x;

    // updateTop();
    // updateLeft();
    // updateWidth();
    // updateHeight();

    // if (overtake_color_properties_)
    // {
    //     require_update_texture_ = true;
    // }
}

int DoubleValueMeter::processMouseEvent(rviz::ViewportMouseEvent &event)
{
    (void)event;
    ROS_INFO_STREAM("ros mouse event...");
    return 0;
}

} // namespace awe_visualization

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(awe_visualization::DoubleValueMeter, rviz::Display)
