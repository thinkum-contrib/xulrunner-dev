/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "UrlClassifierFeatureLoginReputation.h"

#include "mozilla/StaticPrefs.h"

namespace mozilla {
namespace net {

namespace {

#define PREF_PASSWORD_ALLOW_TABLE "urlclassifier.passwordAllowTable"

StaticRefPtr<UrlClassifierFeatureLoginReputation> gFeatureLoginReputation;

}  // namespace

UrlClassifierFeatureLoginReputation::UrlClassifierFeatureLoginReputation()
    : UrlClassifierFeatureBase(NS_LITERAL_CSTRING("login-reputation"),
                               EmptyCString(),  // blacklist tables
                               NS_LITERAL_CSTRING(PREF_PASSWORD_ALLOW_TABLE),
                               EmptyCString(),  // blacklist pref
                               EmptyCString(),  // whitelist pref
                               EmptyCString(),  // blacklist pref table name
                               EmptyCString(),  // whitelist pref table name
                               EmptyCString())  // skip host pref
{}

/* static */ void UrlClassifierFeatureLoginReputation::MaybeShutdown() {
  UC_LOG(("UrlClassifierFeatureLoginReputation: MaybeShutdown"));

  if (gFeatureLoginReputation) {
    gFeatureLoginReputation->ShutdownPreferences();
    gFeatureLoginReputation = nullptr;
  }
}

/* static */ nsIUrlClassifierFeature*
UrlClassifierFeatureLoginReputation::MaybeGetOrCreate() {
  if (!StaticPrefs::browser_safebrowsing_passwords_enabled()) {
    return nullptr;
  }

  if (!gFeatureLoginReputation) {
    gFeatureLoginReputation = new UrlClassifierFeatureLoginReputation();
    gFeatureLoginReputation->InitializePreferences();
  }

  return gFeatureLoginReputation;
}

NS_IMETHODIMP
UrlClassifierFeatureLoginReputation::ProcessChannel(nsIChannel* aChannel,
                                                    const nsACString& aList,
                                                    bool* aShouldContinue) {
  MOZ_CRASH(
      "UrlClassifierFeatureLoginReputation::ProcessChannel should never be "
      "called");
  return NS_OK;
}

NS_IMETHODIMP
UrlClassifierFeatureLoginReputation::GetTables(
    nsIUrlClassifierFeature::listType aListType, nsTArray<nsCString>& aTables) {
  MOZ_ASSERT(aListType == nsIUrlClassifierFeature::whitelist,
             "UrlClassifierFeatureLoginReputation is meant to be used just to "
             "whitelist URLs");
  return UrlClassifierFeatureBase::GetTables(aListType, aTables);
}

NS_IMETHODIMP
UrlClassifierFeatureLoginReputation::HasTable(
    const nsACString& aTable, nsIUrlClassifierFeature::listType aListType,
    bool* aResult) {
  MOZ_ASSERT(aListType == nsIUrlClassifierFeature::whitelist,
             "UrlClassifierFeatureLoginReputation is meant to be used just to "
             "whitelist URLs");
  return UrlClassifierFeatureBase::HasTable(aTable, aListType, aResult);
}

NS_IMETHODIMP
UrlClassifierFeatureLoginReputation::HasHostInPreferences(
    const nsACString& aHost, nsIUrlClassifierFeature::listType aListType,
    nsACString& aPrefTableName, bool* aResult) {
  MOZ_ASSERT(aListType == nsIUrlClassifierFeature::whitelist,
             "UrlClassifierFeatureLoginReputation is meant to be used just to "
             "whitelist URLs");
  return UrlClassifierFeatureBase::HasHostInPreferences(
      aHost, aListType, aPrefTableName, aResult);
}

}  // namespace net
}  // namespace mozilla
