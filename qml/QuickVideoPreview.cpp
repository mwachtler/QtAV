/******************************************************************************
    QtAV:  Media play library based on Qt and FFmpeg
    Copyright (C) 2014 Wang Bin <wbsecg1@gmail.com>
    theoribeiro <theo@fictix.com.br>

*   This file is part of QtAV

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
******************************************************************************/

#include "QuickVideoPreview.h"

namespace QtAV {

QuickVideoPreview::QuickVideoPreview(QQuickItem *parent) :
    QQuickItemRenderer(parent)
{
    connect(&m_extractor, SIGNAL(positionChanged()), this, SIGNAL(timestampChanged()));
    connect(&m_extractor, SIGNAL(frameExtracted(QtAV::VideoFrame)), SLOT(displayFrame(QtAV::VideoFrame)));
    connect(&m_extractor, SIGNAL(error()), SLOT(displayNoFrame()));
}

void QuickVideoPreview::setTimestamp(int value)
{
    m_extractor.setPosition((qint64)value);
}

int QuickVideoPreview::timestamp() const
{
    return (int)m_extractor.position();
}

void QuickVideoPreview::setFile(const QUrl &value)
{
    if (m_file == value)
        return;
    qDebug() << value;
    m_file = value;
    emit fileChanged();
    if (m_file.isLocalFile())
        m_extractor.setSource(m_file.toLocalFile());
    else
        m_extractor.setSource(m_file.toString());
}

QUrl QuickVideoPreview::file() const
{
    return m_file;
}

void QuickVideoPreview::displayFrame(const QtAV::VideoFrame &frame)
{
    receive(frame);
}

void QuickVideoPreview::displayNoFrame()
{
    receive(VideoFrame());
}

} //namespace QtAV
