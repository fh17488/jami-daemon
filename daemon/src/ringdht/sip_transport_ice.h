/*
 *  Copyright (C) 2004-2014 Savoir-Faire Linux Inc.
 *
 *  Author: Adrien Béraud <adrien.beraud@savoirfairelinux.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.
 *
 *  Additional permission under GNU GPL version 3 section 7:
 *
 *  If you modify this program, or any covered work, by linking or
 *  combining it with the OpenSSL project's OpenSSL library (or a
 *  modified version of that library), containing parts covered by the
 *  terms of the OpenSSL or SSLeay licenses, Savoir-Faire Linux Inc.
 *  grants you additional permission to convey the resulting work.
 *  Corresponding Source for a non-source form of such a combination
 *  shall include the source code for the parts of OpenSSL used as well
 *  as that of the covered work.
 */

#pragma once

#include <pjsip.h>
#include <pj/pool.h>
#include <memory>

namespace sfl {
class IceTransport;
}

struct SipIceTransport
{
        SipIceTransport(pjsip_endpoint* endpt, pj_pool_t& pool, long t_type,
                        const std::shared_ptr<sfl::IceTransport>& ice,
                        int comp_id);
        ~SipIceTransport();

        /**
         * To be called once to start receiving packets
         */
        void start();

        std::shared_ptr<sfl::IceTransport> getIceTransport() const {
            return ice_;
        }

        pjsip_transport base;

    private:
        std::unique_ptr<pj_pool_t, decltype(pj_pool_release)&> pool_;
        std::unique_ptr<pj_pool_t, decltype(pj_pool_release)&> rxPool_;
        pjsip_rx_data rdata;
        bool is_registered_ {false};
        const std::shared_ptr<sfl::IceTransport> ice_;
        const int comp_id_;

        pj_status_t send(pjsip_tx_data *tdata, const pj_sockaddr_t *rem_addr,
                         int addr_len, void *token,
                         pjsip_transport_callback callback);

        ssize_t onRecv(uint8_t* buf, size_t len);

        pj_status_t shutdown();

        pj_status_t destroy();
};