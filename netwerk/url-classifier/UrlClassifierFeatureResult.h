/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_net_UrlClassifierFeatureResult_h
#define mozilla_net_UrlClassifierFeatureResult_h

#include "nsIUrlClassifierFeature.h"
#include "nsString.h"

namespace mozilla {
namespace net {

class UrlClassifierFeatureResult final : public nsIUrlClassifierFeatureResult {
 public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIURLCLASSIFIERFEATURERESULT

  UrlClassifierFeatureResult(nsIUrlClassifierFeature* aFeature,
                             const nsACString& aList);

  nsIUrlClassifierFeature* Feature() const { return mFeature; }

  // Comma separated list of tables.
  const nsCString& List() const { return mList; }

 protected:
  ~UrlClassifierFeatureResult();

 private:
  nsCOMPtr<nsIUrlClassifierFeature> mFeature;
  const nsCString mList;
};

}  // namespace net
}  // namespace mozilla

#endif  // mozilla_net_UrlClassifierFeatureResult_h
