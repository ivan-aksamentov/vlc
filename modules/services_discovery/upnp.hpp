/*****************************************************************************
 * upnp.hpp :  UPnP discovery module (libupnp) header
 *****************************************************************************
 * Copyright (C) 2004-2018 VLC authors and VideoLAN
 *
 * Authors: Rémi Denis-Courmont <rem # videolan.org> (original plugin)
 *          Christian Henz <henz # c-lab.de>
 *          Mirsal Ennaime <mirsal dot ennaime at gmail dot com>
 *          Hugo Beauzée-Luyssen <hugo@beauzee.fr>
 *          Shaleen Jain <shaleen@jain.sh>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <wincrypt.h>
#endif

#include "upnp-wrapper.hpp"

#include <vlc_url.h>

namespace SD
{

struct MediaServerDesc
{
    MediaServerDesc( const std::string& udn, const std::string& fName,
                    const std::string& loc, const std::string& iconUrl );
    ~MediaServerDesc();
    std::string UDN;
    std::string friendlyName;
    std::string location;
    std::string iconUrl;
    input_item_t* inputItem;
    bool isSatIp;
    std::string satIpHost;
};


class MediaServerList : public UpnpInstanceWrapper::Listener
{
public:

    MediaServerList( services_discovery_t* p_sd );
    ~MediaServerList();

    bool addServer(MediaServerDesc *desc );
    void removeServer(const std::string &udn );
    MediaServerDesc* getServer( const std::string& udn );
    int onEvent( Upnp_EventType event_type,
                 UpnpEventPtr p_event,
                 void* p_user_data ) override;

private:
    void parseNewServer( IXML_Document* doc, const std::string& location );
    std::string getIconURL( IXML_Element* p_device_elem , const char* psz_base_url );

private:
    services_discovery_t* const m_sd;
    std::vector<MediaServerDesc*> m_list;
};

}

namespace Access
{

class Upnp_i11e_cb
{
public:
    Upnp_i11e_cb( Upnp_FunPtr callback, void *cookie );
    ~Upnp_i11e_cb();
    void waitAndRelease( void );
    static int run( Upnp_EventType, UpnpEventPtr, void *);

private:
    vlc_sem_t       m_sem;
    vlc_mutex_t     m_lock;
    int             m_refCount;
    Upnp_FunPtr     m_callback;
    void*           m_cookie;
};

class MediaServer
{
public:
    MediaServer( stream_t* p_access, input_item_node_t* node );
    ~MediaServer();
    bool fetchContents();

private:
    MediaServer(const MediaServer&);
    MediaServer& operator=(const MediaServer&);

    bool addContainer( IXML_Element* containerElement );
    bool addItem( IXML_Element* itemElement );

    IXML_Document* _browseAction(const char*, const char*,
            const char*, const char*, const char* );
    static int sendActionCb( Upnp_EventType, UpnpEventPtr, void *);

private:
    char* m_psz_root;
    char* m_psz_objectId;
    stream_t* m_access;
    input_item_node_t* m_node;
};

}
